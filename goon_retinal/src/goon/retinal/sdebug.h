#ifndef __GOON_RETINAL_SDEBUG_H
#define __GOON_RETINAL_SDEBUG_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#include <goon/utils/draw.h>
#include <vshow/show_window.h>
#include <vshow/show_video.h>

namespace goon
{
class SDebug
{
private:
    int num_iterations;
    int max_iterations;
    cv::Point seed;
    int img_w;
    int img_h;
    int grid_step;
    Draw oDraw;
    cv::Rect window;
    cv::Vec3f rgb_color;
    cv::Mat mask;
    ShowWindow oShowWindow;
    ShowVideo oShowVideo;

public:

    SDebug();
    ~SDebug();

    // inits necessary data
    void init (int w, int h, int gstep);        

    // sets the background image in the debug image
    void setBase(cv::Mat& image);
   // stores the info to be drawn  
    void storeInfo(cv::Rect exp_window, cv::Vec3f seg_color, cv::Mat exp_mask);    
    // draws the stored info in the debug image
    void drawInfo();

    // resets the progress counter
    void resetCounter() {num_iterations = 0;};        
    // checks if max interations has been reached
    bool checkProgress();    

    void setSeed(cv::Point point) {seed = point;};
    
private:
    // shows the segmentation grid with lines 
    void showGrid();
    // shows the segmentation grid with points 
    void showGrid2();
};
		  	    		  
}  
  
#endif
