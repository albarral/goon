#ifndef __GOON_MONITOR_RETINA_H
#define __GOON_MONITOR_RETINA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "goon/monitor/Draw.h"
#include "goon/data/base/region.h"

namespace goon 
{
class RetinaMonitor
{    
public:    
   
private:
    static log4cxx::LoggerPtr logger;
    Draw oDraw;

public:
//    RetinaMonitor();
//    ~RetinaMonitor();
    
    // Draws an image with the regions obtained by the retinal vision module.
    void drawRegions (cv::Mat& image_cam, std::vector<Region>& listRegions);
    
    cv::Mat& getOutput() {return (oDraw.getOutput());};    

private:
    // obtains the border of a given mask
    //void getBorderMask (cv::Mat& mask, cv::Mat& mask_border);
};
}    
#endif
