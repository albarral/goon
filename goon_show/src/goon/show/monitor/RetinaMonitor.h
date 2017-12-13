#ifndef __GOON_SHOW_RETINAMONITOR_H
#define __GOON_SHOW_RETINAMONITOR_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "tivy/Draw.h"
#include "goon/data/base/region.h"

namespace goon 
{
class RetinaMonitor
{    
public:    
   
private:
    static log4cxx::LoggerPtr logger;
    tivy::Draw oDraw;

public:
//    RetinaMonitor();
//    ~RetinaMonitor();
    
    // Draws an image with the given list of regions 
    void drawRegions (cv::Mat& image_cam, std::list<Region>& listRegions);
    
    cv::Mat& getOutput() {return (oDraw.getOutput());};    

private:
    // obtains the border of a given mask
    //void getBorderMask (cv::Mat& mask, cv::Mat& mask_border);
};
}    
#endif