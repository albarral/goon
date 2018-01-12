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
#include <goon/features/color/rgb_color.h>

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
    numSegmenters = oConfigRetinal.getSegmentationNumThreads();
    pRetina = 0;
    //bdebug = false;    
}

// destructor
Segmentation4::~Segmentation4()
{
    // request segmenter threads to stop
    for (int i=0; i<numSegmenters; i++)        
        oSegmenters[i].off();
  
    // wait for them to finish
    for (int i=0; i<numSegmenters; i++)        
        oSegmenters[i].wait();
}

void Segmentation4::init(Retina& oRetina, int img_w, int img_h)
{        
    LOG4CXX_DEBUG(logger, "resize ...");

    //    if (bdebug)
    //        oDebug.init(img_w, img_h, GRID_STEP);
    pRetina = &oRetina;    
    IMG_W = img_w;
    IMG_H = img_h;    
    
    // build the list of seeds
    buildRandomSeeds(img_w, img_h);    
    // create the segmentation mask (to be shared by all segmenters)
    mask_segmented = cv::Mat::zeros(IMG_H, IMG_W, CV_8UC1); 
    
    // init the segmenters
    initSegmenters(oRetina);
}

void Segmentation4::setMinDetail (float value) {MIN_DETAIL = value;}

void Segmentation4::setNumSamples (int value) {NUM_SAMPLES = value;}

void Segmentation4::initSegmenters(Retina& oRetina)
{           
    // compute minimum detail size
    int minDetailSize = IMG_W * IMG_H * MIN_DETAIL;   

    // seeds will be equally distributed among segmenters
    int seeds4each = vec_seeds.size()/numSegmenters;
    int samples = NUM_SAMPLES/numSegmenters;
    std::vector<cv::Point>::iterator it_firstSeed;
    std::vector<cv::Point>::iterator it_lastSeed;
    it_lastSeed = vec_seeds.begin();
        
    // creation of each individual segmenter
    for (int i=0; i<numSegmenters; i++)
    {
        //create segmenter
        Segmenter& oSegmenter = oSegmenters[i];

        // create its list of seeds
        it_firstSeed = it_lastSeed;
        it_lastSeed = it_firstSeed + seeds4each;
        std::vector<cv::Point> listSeeds(it_firstSeed, it_lastSeed);

        // configurate it 
        oSegmenter.setID(i+1);
        oSegmenter.init(oRetina, mask_segmented);
        oSegmenter.config(listSeeds, samples, minDetailSize);
        oSegmenter.setFrequency(100);   // to wait small delays
    }

    // start all segmenter threads
    for (int i=0; i<numSegmenters; i++)
        oSegmenters[i].on();
}

// This function performs floodfills from random seeds to segment homogeneous color regions from the image.
int Segmentation4::extractRegions (cv::Mat& image_cam, cv::Mat& image_hsv)
{
//    if (bdebug)    
//        oDebug.setBase(image_cam);
    
    // Reset segmentation mask 
    mask_segmented.setTo(0);
    
    std::vector<int> listBeats = getSegmenterBeats();
        
    launchSegmenters(image_cam, image_hsv);
        
    // wait for all segmenters to end their job
    waitAllFinished(listBeats);
    
    LOG4CXX_DEBUG(logger, "extracted regions = " << pRetina->getNumRegions());
}
  

void Segmentation4::launchSegmenters(cv::Mat& image_cam, cv::Mat& image_hsv)
{
    for (int i=0; i<numSegmenters; i++)
        oSegmenters[i].newRequest(image_cam, image_hsv);
}

std::vector<int> Segmentation4::getSegmenterBeats()
{
    std::vector<int> listBeats;

    for (int i=0; i<numSegmenters; i++)
    {
        listBeats.push_back(oSegmenters[i].getBeat());
    }
    
    return listBeats;
}

void Segmentation4::waitAllFinished(std::vector<int>& listBeats)
{
    bool banyWorking = true;
    // wait till all segmenters have finished
    while (banyWorking)
    {
        banyWorking = false;
        // for each segmenter, check if it has produced a new beat
        for (int i=0; i<numSegmenters; i++)
        {        
            if (oSegmenters[i].getBeat() == listBeats[i])            
            {
                banyWorking = true;
                break;
            }
        }
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

    LOG4CXX_INFO(logger, "new random seeds " << vec_seeds.size());
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
