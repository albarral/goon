#ifndef __GOON_SHOW_ROISMONITOR_H
#define __GOON_SHOW_ROISMONITOR_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "tivy/Draw.h"
#include "goon/data/base/roi.h"

namespace goon 
{
class ROIsMonitor
{    
public:    
   
private:
    static log4cxx::LoggerPtr logger;
    tivy::Draw oDraw;

public:
//    ROIsMonitor();
//    ~ROIsMonitor();
    
    // Draws an image with the given list of ROI's.
    void drawRois(cv::Mat& image_cam, std::list<ROI>& listROIs, int focusedROI);

    // draws the given fps value
    void drawFPS(float fps);
    
    cv::Mat& getOutput() {return (oDraw.getOutput());};        
};
}    
#endif
