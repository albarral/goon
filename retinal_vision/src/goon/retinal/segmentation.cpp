/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include <algorithm>
#include <unistd.h> // for usleep

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
    pRetina = 0;
    //bdebug = false;
}

// destructor
Segmentation4::~Segmentation4()
{
    oSegmenter.off();
    oSegmenter.wait();
}

void Segmentation4::init(Retina& oRetina, int img_w, int img_h)
{        
    LOG4CXX_DEBUG(logger, "resize ...");

    //    if (bdebug)
    //        oDebug.init(img_w, img_h, GRID_STEP);
    pRetina = &oRetina;    
    IMG_W = img_w;
    IMG_H = img_h;    
    // compute minimum detail size
    int minRegionSize = img_w * img_h * MIN_DETAIL;   
    // build the list of seeds
    buildRandomSeeds(img_w, img_h);    
//    int seeds4each = vec_seeds.size()/2;
//    std::vector<cv::Point> vec_seeds1(vec_seeds.begin(), vec_seeds.begin() + seeds4each);
//    std::vector<cv::Point> vec_seeds2(vec_seeds.begin() + seeds4each, vec_seeds.begin() + 2*seeds4each);
    // create the segmentation mask (to be shared by all segmenters)
    mask_segmented = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC1); 
    // init the segmenters
    oSegmenter.setID(1);
    oSegmenter.init(oRetina, mask_segmented);
    oSegmenter.config(vec_seeds, NUM_SAMPLES, minRegionSize);
    oSegmenter.setFrequency(20);
    oSegmenter.on();
}

void Segmentation4::setMinDetail (float value) {MIN_DETAIL = value;}

void Segmentation4::setNumSamples (int value) {NUM_SAMPLES = value;}

// This function performs floodfills from random seeds to segment homogeneous color regions from the image.
int Segmentation4::extractRegions (cv::Mat& image_cam, cv::Mat& image_hsv)
{
//    if (bdebug)    
//        oDebug.setBase(image_cam);
    
    // Reset segmentation mask 
    mask_segmented.setTo(0);
    
    launchSegmenters(image_cam, image_hsv);
    
    wait4Segmenters();
        
    //LOG4CXX_TRACE(logger, "extracted regions = " << pRetina->getNumRegions());
}
  

bool Segmentation4::launchSegmenters(cv::Mat& image_cam, cv::Mat& image_hsv)
{
    if (oSegmenter.isReady())
    {
        oSegmenter.newRequest(image_cam, image_hsv);
        // wait for it to start working
        while (!oSegmenter.isWorking())
            usleep(10000); // 10ms
        return true;
    }
    else 
        return false;    
}

void Segmentation4::wait4Segmenters()
{
    int numSegmenters = 1;
    int numFinished = 0;
    while (numFinished < numSegmenters)
    {
        if (oSegmenter.isReady())
            numFinished++;
        usleep(10000); // 10ms
    }
}


void Segmentation4::buildRandomSeeds(int img_w, int img_h)
{
    cv::Point seed;
    
    vec_seeds.clear();
    
    // fill the seeds vector with all the pixels in the image
    for (int x=0; x<img_w; x++)
        for (int y=0; y<img_h; y++)
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
