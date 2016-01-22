#ifndef __GOON_RETINAL_SEGMENTATION3_H
#define __GOON_RETINAL_SEGMENTATION3_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <deque>
#include "opencv2/core/core.hpp"
#include <log4cxx/logger.h>

#include <goon/data/retina.h>
#include <goon/utils/trigger.h>
#include "goon/retinal/Exploration.h"
#include "goon/retinal/ColorGrid.h"
#include "goon/retinal/HSVEssence.h"
//#include "goon/retinal/sdebug.h"

// This class implements the segmentation of an image into color homogeneous regions.
// HOW: It does so by triggering floodfill processes from random seeds (using the RGB color space). 
// OUTPUT: The extracted regions (masks included) are added to the external Retina object.
// IMPORTANT: It uses a color grid to allow the handling of soft color evolutions within a region.
// DRAWBACKS: In blurred images undesired region overflows may appear due to uncontrolled color evolutions. 
// ON RESEARCH: A color essence module is being tested to help avoid these overflows (using the HSV color space). 
namespace goon
{
class Segmentation
{
private:
    static log4cxx::LoggerPtr logger;
    int IMG_W;            // image width 
    int IMG_H;             // image height
    int GRID_STEP;      // separation between grid nodes (pixels)
    float MIN_DETAIL;      // minimum area of details allowed for detection (fraction of image area)
    int NUM_SAMPLES;    // number of seeds used to extract regions
    std::vector<cv::Point> vec_seeds;
    std::deque<cv::Point> deq_floodfill;  
    cv::Mat mask_segmented;
    Exploration oExploration;   // class for image exploration (owns mask_explored and mask_region)       
    ColorGrid oColorGrid;        // class for handling the region's local color
    HSVEssence oHSVEssence; // class for handling the region's central color
    Trigger oSizeTrigger;
    // for debug
    //bool bdebug;
    //SDebug oDebug;    

public:

    Segmentation();
    ~Segmentation();

    // change of parameters
    void setSizes (int img_w, int img_h);
    void setGridStep(int grid_step);
    void setMinDetail(float value);
    void setNumSamples(int value);

    int extractRegions(cv::Mat& image_cam, cv::Mat& image_hsv, Retina& oRetina);
    // This function performs floodfills from random seeds to segment homogeneous color regions from the image.

    // Returns the segmentation mask.
    cv::Mat& getSegmentedMask() {return mask_segmented;};

private:

    // Resizes all masks, grids and seeds vector
    void resize();
        
    // KEY FUNCTION OF THE RETINAL VISION PROCESS
    // Expands a region with homogeneous color from the specified seed. 
    // It returns the area of the obtained region.
    int floodFill(cv::Mat& image_cam, cv::Mat& image_hsv, cv::Point& seed);
        
    // Builds the seeds vector (a randomly ordered sequence of image pixels)
    void buildRandomSeeds();
    
    // Returns a random index of the seeds vector.
    int getRandomIndex();
    
    // shows the present state of the segmentation process in an image for debugging (segmented pixels, computed colors ...)  
    void showProgress();
};
		  	    		  
}  
  
#endif
