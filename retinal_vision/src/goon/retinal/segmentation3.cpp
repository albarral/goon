/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include <algorithm>

#include "goon/retinal/segmentation3.h"
#include "goon/retinal/ColorNode.h"
#include <goon/data/base/region.h>
#include <goon/utils/rgb_color.h>
#include <goon/utils/distance.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr Segmentation::logger(Logger::getLogger("goon.retinal"));
				 				 				 					
// constructor
Segmentation::Segmentation ()
{
    // default values
    GRID_STEP = 10;
    MIN_DETAIL = 0.001;        // regions accepted from at least 0.1% of image area
    NUM_SAMPLES = 2000;   // 2000 samples per iteration          

    // trigger to update region's central color every 10% size increase (initially every 100 pixels)  
    oSizeTrigger.setParams(0.1, 100);
    
    //bdebug = false;
}

// destructor
Segmentation::~Segmentation()
{
}

void Segmentation::setSizes(int img_w, int img_h)
{        
    IMG_W = img_w;
    IMG_H = img_h;    
        
//    if (bdebug)
//        oDebug.init(img_w, img_h, GRID_STEP);
    
    resize();           
}

void Segmentation::setGridStep(int grid_step)
{        
    GRID_STEP = grid_step;
    oColorGrid.resize (IMG_W, IMG_H);
}

void Segmentation::setMinDetail (float value) {MIN_DETAIL = value;}

void Segmentation::setNumSamples (int value) {NUM_SAMPLES = value;}


void Segmentation::resize()
{        
    LOG4CXX_DEBUG(logger, "resize ...");

    mask_segmented = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC1);    
    oExploration.resize(IMG_W, IMG_H);        
    oColorGrid.resize (IMG_W, IMG_H);

    buildRandomSeeds();    
}


// This function performs floodfills from random seeds to segment homogeneous color regions from the image.
int Segmentation::extractRegions (cv::Mat& image_cam, cv::Mat& image_hsv, Retina& oRetina)
{
    Region oRegion;
    int num_seeds = 0;  
    int region_size;
    int min_region_size = IMG_W * IMG_H * MIN_DETAIL;   // allows detail changes

//    if (bdebug)    
//        oDebug.setBase(image_cam);
    
    // Reset segmentation mask 
    mask_segmented = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC1);
    
    // start getting seeds from a random position in the vector
    std::vector<cv::Point>::iterator it_seed = vec_seeds.begin();
    std::advance(it_seed, getRandomIndex());

    while (num_seeds < NUM_SAMPLES)
    {
        // if seed not segmented, expand from it a new region 		
        if (mask_segmented.at<ushort>(it_seed->y, it_seed->x) == 0)
        {			
            region_size = floodFill(image_cam, image_hsv, *it_seed);

            // if the region is big enough, accept it 
            if (region_size > min_region_size)
            {
                // build the region (type, mass, mask, window, grid, color and position)
                oRegion.setType(Region::eREG_SIMPLE); 
                oRegion.setMass(region_size);
                oRegion.createMask(oExploration.getRegionMask(), oExploration.getWindow());
                //oRegion.setGrid(oColorGrid.getSamplesGrid());
                oColorGrid.computeMeanColor(oExploration.getWindow());    
                oRegion.setRGB(oColorGrid.getColorMean());	
                RGBColor::toHSV(oRegion.getRGB(), oRegion.getHSV());
                oRegion.setSeed(*it_seed);

                // and add it to the retina (ID assigned there)
                oRetina.addRegion(oRegion);

                LOG4CXX_TRACE(logger, "-> region " << oRegion.getID());
                //LOG4CXX_TRACE(logger, "mass =" << oRegion.getMass());
                cv::Vec3f hsv = oHSVEssence.getMainColor();
                LOG4CXX_TRACE(logger, "hsv color = " << (int)hsv[0] << ", " << (int)hsv[1]*100/255 << ", " << (int)hsv[2]*100/255); 
                //cv::Vec3f hsv_dev = oCentralColor.getColorDev();                
                //LOG4CXX_TRACE(logger, "hsv dev = (" << (int)hsv_dev[0] << ", " << (int)hsv_dev[1]*100/255 << ", " << (int)hsv_dev[2]*100/255 << ")"); 
                                                                 
//                if (bdebug)                            
//                    showProgress();
            }
        }
        
        num_seeds++;
        
        // get next seed (if end of vector reached, follow at the beginning)
        it_seed++;
        if (it_seed == vec_seeds.end())
            it_seed = vec_seeds.begin();
    } // end while    
    
    LOG4CXX_TRACE(logger, "extracted regions = " << oRetina.getNumRegions());
}


// This function obtains homogeneous regions by expanding from an initial seed pixel to all connected pixels with similar color.
int Segmentation::floodFill(cv::Mat& image_cam, cv::Mat& image_hsv, cv::Point& seed) 
{
    int right_border, bottom_border;
    cv::Vec3b pixel_rgb, seed_rgb;
    cv::Vec3i pixel_hsv; 
    cv::Vec3f local_rgb; 
    bool bInBorder;
    cv::Point point, point_exp;
    int num_pixels = 0;    

    float SQR_SAME = RGBColor::getSqrSameDist();

    //LOG4CXX_TRACE(logger, "floodfill " << "(" << seed.x << ", " << seed.y << ")");

//    if (bdebug)                                    
//        oDebug.resetCounter();
    
    // init support classes
    oExploration.prepare(image_cam, image_hsv);    
    oExploration.setForbiddenMask(mask_segmented);    
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
                    if ((Distance::getEuclidean3s(local_rgb, pixel_rgb) < SQR_SAME) 
                            && oHSVEssence.compare(pixel_hsv) < 1.0)
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
    
    return num_pixels;
}

    
void Segmentation::buildRandomSeeds()
{
    cv::Point seed;
    
    vec_seeds.clear();
    
    // fill the seeds vector with all the pixels in the image
    for (int x=0; x<IMG_W; x++)
        for (int y=0; y<IMG_H; y++)
        {
            seed.x = x;
            seed.y = y;
            vec_seeds.push_back(seed);
        }
    
    // shuffle the vector for random ordering
    std::random_shuffle(vec_seeds.begin(), vec_seeds.end());

    LOG4CXX_DEBUG(logger, "new random seeds " << vec_seeds.size());
}


int Segmentation::getRandomIndex()
{
    return (vec_seeds.size() * (float) std::rand() / RAND_MAX);
}
		

//void Segmentation::showProgress()
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
