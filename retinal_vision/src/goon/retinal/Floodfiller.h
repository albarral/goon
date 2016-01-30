#ifndef __GOON_RETINAL_FLOODFILLER_H
#define __GOON_RETINAL_FLOODFILLER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <thread>
#include <mutex>
#include <deque>
#include "opencv2/core/core.hpp"
#include <log4cxx/logger.h>

#include <goon/utils/trigger.h>
#include "goon/retinal/Exploration.h"
#include "goon/retinal/ColorGrid.h"
#include "goon/retinal/HSVEssence.h"

// This class extracts a color homogenous region from an image beginning with a single seed pixel.
// It runs in its own thread, allowing simultaneous extraction of multiple regions.
// It works doing a floodfill process (an expansion to adjacent pixels with similar color) from the specified seed. 
// For the color similarity both the RGB and HSV spaces are used.
// The expansion is limited by a forbidden mask, used to avoid overlapping of extracted regions.
// OUTPUT: The extracted region is represented by a mask and main color.
// IMPORTANT: It uses a color grid to allow the handling of soft color evolutions within a region.
// DRAWBACKS: In blurred images undesired region overflows may appear due to uncontrolled color evolutions. 
// ON RESEARCH: An HSV color essence module is being tested to help avoid these overflows (uses the HSV color space). 
namespace goon
{
class Floodfiller
{
public:
    enum eState
    {
        eFF_OFF,            // not initialized
        eFF_READY,        // ready for a new action
        eFF_ON,             // running a new action
        eFF_FINISHED     // last action finished 
    };
    
private:
    static log4cxx::LoggerPtr logger;
    std::mutex mutex;
    std::thread t;              // the thread container
    int state;          
    Exploration oExploration;   // class for image exploration (owns mask_explored and mask_region)       
    ColorGrid oColorGrid;        // class for handling the region's local color
    HSVEssence oHSVEssence; // class for handling the region's central color
    Trigger oSizeTrigger;
    cv::Point seed;             // initial seed 
    cv::Mat image_cam;      // input image (RGB))
    cv::Mat image_hsv;       // input image (HSV)   
    std::deque<cv::Point> deq_floodfill;  // list of pixels to which the region may expand (starts with only the seed)
    int num_pixels;
    float SAME_RGB_LOCAL;       // required RGB similarity vs local color
    float SAME_HSV_GLOBAL;     // required HSV similarity vs global color 

    // for debug
    //bool bdebug;
    //SDebug oDebug;    

public:
    Floodfiller();
    ~Floodfiller();

    // Initializes the module and auxiliary classes. 
    // The module will not work if not first initialized.
    void init(cv::Mat& mask_segmented);
    // run a region extraction from the given seed
    int run(cv::Point& seed, cv::Mat& image_cam, cv::Mat& image_hsv);
    // Mark Floodfiller object as used. That is, set its state to READY.
    void used();

    // checks for different module states (thread safe)
    bool isReady();
    bool isOn();
    bool isFinished();
    
    // get features of the extracted region
    int getRegionArea();
    cv::Mat& getRegionMask();
    cv::Rect& getRegionWindow();
    cv::Vec3f& getRegionColor();
    
private:
    // sets the module state (thread safe)
    void setState(int value);
    // KEY FUNCTION OF THE RETINAL VISION PROCESS
    // Expands a region with homogeneous color from the specified seed. 
    void floodFill();

    // shows the present state of the segmentation process in an image for debugging (segmented pixels, computed colors ...)  
    //void showProgress();
};
		  	    		  
}  
  
#endif
