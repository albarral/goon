#ifndef __GOON_RETINAL_SEGMENTATION_H
#define __GOON_RETINAL_SEGMENTATION_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"
#include <log4cxx/logger.h>

#include <goon/data/retina.h>
#include "goon/retinal/Segmenter.h"

// This class implements the segmentation of an image into color homogeneous regions.
// MULTITHREADED
// It performs multiple region extractions in parallel by means of Floodfiller objects, each of them working in its own thread.
namespace goon
{
class Segmentation4
{
private:
    static log4cxx::LoggerPtr logger;
    // params
    int IMG_W;            // image width 
    int IMG_H;             // image height
    float MIN_DETAIL;      // minimum area of details allowed for detection (fraction of image area)
    int NUM_SAMPLES;    // number of seeds used to extract regions
    // shared data
    Retina* pRetina;                    // pointer to shared retina
    // logic
    std::vector<cv::Point> vec_seeds;
    cv::Mat mask_segmented;
    Segmenter oSegmenters[4];   // array of segmenters, objects for region extractions
    int numSegmenters;

public:

    Segmentation4();
    ~Segmentation4();

    // Resizes all masks, grids and seeds vector
    void init(Retina& oRetina, int img_w, int img_h);

    // change of parameters
    void setGridStep(int grid_step);
    void setMinDetail(float value);
    void setNumSamples(int value);

    int extractRegions(cv::Mat& image_cam, cv::Mat& image_hsv);

    // Returns the segmentation mask.
    cv::Mat& getSegmentedMask() {return mask_segmented;};

private:                
    // Builds the seeds vector (a randomly ordered sequence of image pixels)
    void buildRandomSeeds(int img_w, int img_h);    
    // Returns a random index of the seeds vector.
    int getRandomIndex();
    
    // initializes the segmenter objects
    void initSegmenters(Retina& oRetina);    
    /// send request to all Segmenters
    void launchSegmenters(cv::Mat& image_cam, cv::Mat& image_hsv);    
    // gets the number of working segmenters
    int getWorkingSegmenters();
    // get beats of all segmenters
    std::vector<int> getSegmenterBeats();
    // wait till all segmenters have finished their job
    void waitAllFinished(std::vector<int>& listBeats);
        
    // shows the present state of the segmentation process in an image for debugging (segmented pixels, computed colors ...)  
    void showProgress();
};
		  	    		  
}  
  
#endif
