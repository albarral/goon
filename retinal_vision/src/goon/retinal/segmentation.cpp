/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include <algorithm>
#include <unistd.h>

#include "goon/retinal/segmentation.h"
#include "goon/retinal/ConfigRetinal.h"
#include "goon/retinal/Floodfiller.h"
#include <goon/data/base/region.h>
#include <goon/utils/rgb_color.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr Segmentation4::logger(Logger::getLogger("goon.retinal"));
				 				 				 					
// constructor
Segmentation4::Segmentation4 ()
{
    // default values
    ConfigRetinal oConfigRetinal;
    MIN_DETAIL = oConfigRetinal.getSegmentationMinDetail();        // regions accepted from at least 0.1% of image area
    NUM_SAMPLES = oConfigRetinal.getSegmentationNumSamples();   // 2000 samples per iteration          

    //bdebug = false;
}

// destructor
Segmentation4::~Segmentation4()
{
}

void Segmentation4::init(int img_w, int img_h)
{        
    LOG4CXX_DEBUG(logger, "resize ...");

    //    if (bdebug)
    //        oDebug.init(img_w, img_h, GRID_STEP);
    IMG_W = img_w;
    IMG_H = img_h;    
    mask_segmented = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC1); 
    oFloodfiller.init(mask_segmented);
    oFloodfiller2.init(mask_segmented);
    buildRandomSeeds();    
}

void Segmentation4::setMinDetail (float value) {MIN_DETAIL = value;}

void Segmentation4::setNumSamples (int value) {NUM_SAMPLES = value;}

// This function performs floodfills from random seeds to segment homogeneous color regions from the image.
int Segmentation4::extractRegions (cv::Mat& image_cam, cv::Mat& image_hsv, Retina& oRetina)
{
    Region oRegion;
    int num_seeds = 0;  
    int num_floodfills = 0;  
    int region_size;
    int min_region_size = IMG_W * IMG_H * MIN_DETAIL;   // recomputes to allow changes in minimum detail size
    bool bnextSeed = false;

//    if (bdebug)    
//        oDebug.setBase(image_cam);
    
    // Reset segmentation mask 
    mask_segmented.setTo(0);
    
    // start getting seeds from a random position in the vector
    std::vector<cv::Point>::iterator it_seed = vec_seeds.begin();
    std::advance(it_seed, getRandomIndex());
    while (num_seeds < NUM_SAMPLES)
    {        
        // if seed not segmented, expand from it a new region 		
        if (mask_segmented.at<ushort>(it_seed->y, it_seed->x) == 0)
        {		
            // keep the seed if no floodfiller available
            bnextSeed = launchNewFloodfill(*it_seed, image_cam, image_hsv);
            
            Floodfiller* pFloodfiller = check4FinishedFloodfills();
            
            if (pFloodfiller != 0)
            {
                num_floodfills++;
                region_size = pFloodfiller->getRegionArea();

                // if the region is big enough, accept it 
                if (region_size > min_region_size)
                {
                    // build the region (type, mass, mask, window, grid, color and position)
                    oRegion.setType(Region::eREG_SIMPLE); 
                    oRegion.setMass(region_size);
                    oRegion.createMask(pFloodfiller->getRegionMask(), pFloodfiller->getRegionWindow());
                    //oRegion.setGrid(oColorGrid.getSamplesGrid());
                    oRegion.setRGB(pFloodfiller->getRegionColor());	
                    RGBColor::toHSV(oRegion.getRGB(), oRegion.getHSV());
                    oRegion.setSeed(*it_seed);

                    // and add it to the retina (ID assigned there)
                    oRetina.addRegion(oRegion);
                    
                    LOG4CXX_TRACE(logger, "-> region " << oRegion.getID());
                    //LOG4CXX_TRACE(logger, "mass =" << oRegion.getMass());
                    //cv::Vec3f hsv = oHSVEssence.getMainColor();
                    //LOG4CXX_TRACE(logger, "hsv color = " << (int)hsv[0] << ", " << (int)hsv[1]*100/255 << ", " << (int)hsv[2]*100/255); 
    //                if (bdebug)                            
    //                    showProgress();
                }
                else
                    LOG4CXX_TRACE(logger, "-> region ignored");
                
                // used FF is ready again
                pFloodfiller->used();
            }                
        }      
        else
            bnextSeed = true;
            
        // new seed to be used
        if (bnextSeed)
        {
            num_seeds++;        
            // get next seed (if end of vector reached, follow at the beginning)
            it_seed++;
            if (it_seed == vec_seeds.end())
                it_seed = vec_seeds.begin();            
        }
    } // end while    
    
    LOG4CXX_TRACE(logger, "extracted regions = " << oRetina.getNumRegions() << " - num floodfills = " << num_floodfills);
}
  

bool Segmentation4::launchNewFloodfill(cv::Point& seed, cv::Mat& image_cam, cv::Mat& image_hsv)
{
    Floodfiller* pFloodfiller = 0;
    
    if (oFloodfiller.isReady())
        pFloodfiller = &oFloodfiller;
    else if (oFloodfiller2.isReady())
        pFloodfiller = &oFloodfiller2;

    if (pFloodfiller != 0)
    {
        pFloodfiller->run(seed, image_cam, image_hsv);    
        return true;
    }
    else 
        return false;    
}


Floodfiller* Segmentation4::check4FinishedFloodfills()
{
    Floodfiller* pFloodfiller = 0;
    
    if (oFloodfiller.isFinished())
        pFloodfiller = &oFloodfiller;
    else if (oFloodfiller2.isFinished())
        pFloodfiller = &oFloodfiller2;
    
    return pFloodfiller;    
}

void Segmentation4::buildRandomSeeds()
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


int Segmentation4::getRandomIndex()
{
    return (vec_seeds.size() * (float) std::rand() / RAND_MAX);
}
		

//void Segmentation4::showProgress()
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
