/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include <algorithm>

#include "goon/retinal/Floodfiller.h"
#include "goon/retinal/ConfigRetinal.h"
#include <goon/utils/rgb_color.h>
#include <goon/utils/distance.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr Floodfiller::logger(Logger::getLogger("goon.retinal"));
				 				 				 					
// constructor
Floodfiller::Floodfiller ()
{
    ConfigRetinal oConfigRetinal;

    state = Floodfiller::eFF_OFF;
        
    // trigger used to update the region's central color 
    oSizeTrigger.setParams(oConfigRetinal.getColorEssenceUpdateChangeFactor(), oConfigRetinal.getColorEssenceUpdateMinChange());  
    SAME_RGB_LOCAL = RGBColor::getSqrSameDist();
    SAME_HSV_GLOBAL = oConfigRetinal.getColorEssenceHSVSimilarity();

    //bdebug = false;
}

// destructor
Floodfiller::~Floodfiller()
{
}

void Floodfiller::init(cv::Mat& mask_segmented)
{
    // initialize auxiliary classes
    int w = mask_segmented.cols;
    int h = mask_segmented.rows;
    oExploration.setForbiddenMask(mask_segmented);    
    oExploration.resize(w, h);        
    oColorGrid.resize (w, h);
    // ready for use
    setState(Floodfiller::eFF_READY);
}

void Floodfiller::setState(int value)
{
    std::lock_guard<std::mutex> locker(mutex);
    state = value;    
}

// runs a region extraction from the given seed (launching an own thread)   
int Floodfiller::run(cv::Point& seed, cv::Mat& image_cam, cv::Mat& image_hsv)
{
    // launch thread only if not running already
    if (isReady() || isFinished())
    {
        this->seed = seed;
        this->image_cam = image_cam;
        this->image_hsv = image_hsv;        
        setState(Floodfiller::eFF_ON);
        t = std::thread(&Floodfiller::floodFill, this);    
        // detach the thread if the thread object is to be reused
        t.detach();
        return 0;
    }
    else 
    {
        LOG4CXX_ERROR(logger, "Floodfiller run failed!");
        return -1;
    }
}

void Floodfiller::used()
{
    // put the state to READY (if not ON at this moment)
    if (!isOn())
        setState(Floodfiller::eFF_READY);    
}

// This function obtains homogeneous regions by expanding from an initial seed pixel to all connected pixels with similar color.
void Floodfiller::floodFill() 
{
    int right_border, bottom_border;
    cv::Vec3b pixel_rgb, seed_rgb;
    cv::Vec3i pixel_hsv; 
    cv::Vec3f local_rgb; 
    bool bInBorder;
    cv::Point point, point_exp;

    LOG4CXX_TRACE(logger, "floodfill " << "(" << seed.x << ", " << seed.y << ")");

//    if (bdebug)                                    
//        oDebug.resetCounter();
    
    num_pixels = 0;    

    // init support classes
    oExploration.prepare(image_cam, image_hsv);    
    oColorGrid.clear();
    oHSVEssence.reset();
    oSizeTrigger.reset();

    right_border = image_cam.cols - 1;
    bottom_border = image_cam.rows - 1;

    // store initial seed
    oExploration.firstWindow(seed);
    oExploration.moveSeed(seed);
    oExploration.getSeedRGB(seed_rgb);
    oColorGrid.selectNode(seed);
    oColorGrid.updateLocalColor(seed_rgb);
    
    deq_floodfill.push_back(seed);

    // if seed pixels available, get a new one and check its 4 connected neighbours
    while (!deq_floodfill.empty()) 
    {
        // read points in FIFO order
        point = deq_floodfill.front();
        deq_floodfill.pop_front();
        
        bInBorder = (point.x == 0 || point.x == right_border || point.y == 0 || point.y == bottom_border);

        // avoid expanding to the border
        if (!bInBorder) 
        {
            oExploration.moveSeed(point);
                        
            // obtain the seed's local color (always valid as its node was updated on acceptance)
            oColorGrid.selectNode(point);
            oColorGrid.getLocalColor(local_rgb);

            // update the region's color essence every 10% growth
            if (oSizeTrigger.check(num_pixels))
            {
                oSizeTrigger.update(num_pixels);

                oExploration.computeWindow();   
                oColorGrid.computeMeanColor(oExploration.getWindow());                     
                oHSVEssence.setMainFromRGB(oColorGrid.getColorMean());                

                //oCentralColor.computeColorDeviation(oColorGrid.getLocalGrid(), oColorGrid.getGridWindow(), oColorGrid.getMaskSamples());                
                //if (oCentralColor.typeChanged())
                    //LOG4CXX_TRACE(logger, oCentralColor.getName());                                         
            }

            // analyze the 4 pixels adjacent to the new obtained seed
            for (int i = Exploration::eEAST; i < Exploration::eLOCS_DIM; i++) 
            {
                if (oExploration.checkAdjacent(i) == Exploration::eFREE)
                {                    
                    oExploration.getPixelRGB(pixel_rgb);                          
                    oExploration.getPixelHSV(pixel_hsv);
                                    
                    // if pixel's color is similar to local color and similar to central color -> include it in the region
                    if ((Distance::getEuclidean3s(local_rgb, pixel_rgb) < SAME_RGB_LOCAL) 
                            && oHSVEssence.compare(pixel_hsv) < SAME_HSV_GLOBAL)
                    {
                        num_pixels++;

                        // include pixel in region (mask, color grid, mass)
                        oExploration.markPixel(true);
                        point_exp = oExploration.getPixel();
                        
                        oColorGrid.selectNode(point_exp);
                        oColorGrid.updateLocalColor(pixel_rgb);  
                        
                        // and make him another seed
                        deq_floodfill.push_back(point_exp);           
                                                
//                        if (bdebug && oDebug.checkProgress())
//                            showProgress();
                    }
                    // otherwise -> reject it
                    else
                        oExploration.markPixel(false);
                }
            } // end for
        } // end if not in border
    } // end while
    
    oExploration.computeWindow();
    
    LOG4CXX_TRACE(logger, "floodfill end (" << num_pixels << " pixels)");

    // set to finished
    setState(Floodfiller::eFF_FINISHED);    
}

bool Floodfiller::isReady()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state == Floodfiller::eFF_READY);  
}

bool Floodfiller::isOn()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state == Floodfiller::eFF_ON);  
}

bool Floodfiller::isFinished()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state == Floodfiller::eFF_FINISHED);  
}

int Floodfiller::getRegionArea()
{
    return num_pixels;
};    

cv::Mat& Floodfiller::getRegionMask()
{
    return oExploration.getRegionMask();   
}

cv::Rect& Floodfiller::getRegionWindow()
{
    return oExploration.getWindow();    
}
    
cv::Vec3f& Floodfiller::getRegionColor()
{
    oColorGrid.computeMeanColor(oExploration.getWindow());    
    return (oColorGrid.getColorMean());	
}

//void Floodfiller::showProgress()
//{
//    // compute present mask, window and color
//    oExploration.computeWindow();       
//    cv::Mat mask_progress = oExploration.getRegionMask()(oExploration.getWindow());
//    oColorGrid.computeMeanColor(oExploration.getWindow());                                                                            
//    
//    // draw it in a debug image
//    oDebug.storeInfo(oExploration.getWindow(), oColorGrid.getColorMean(), mask_progress);  
//    oDebug.drawInfo();
//}

}