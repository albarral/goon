#ifndef __GOON_MONITOR_ROIS_H
#define __GOON_MONITOR_ROIS_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "goon/monitor/Draw.h"
#include "goon/data/base/roi.h"

namespace goon 
{
class ROIsMonitor
{    
public:    
   
private:
    static log4cxx::LoggerPtr logger;
    Draw oDraw;

public:
//    ROIsMonitor();
//    ~ROIsMonitor();
    
    // Draws an image with the given list of ROI's.
    void drawRois(cv::Mat& image_cam, std::vector<ROI>& listROIs);

    // draws the given fps value
    void drawFPS(float fps);
    
    cv::Mat& getOutput() {return (oDraw.getOutput());};        
};
}    
#endif
