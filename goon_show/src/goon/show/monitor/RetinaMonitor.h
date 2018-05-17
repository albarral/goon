#ifndef __GOON_SHOW_RETINAMONITOR_H
#define __GOON_SHOW_RETINAMONITOR_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "tron/display/Draw.h"
#include "goon/data/base/region.h"
#include "goon/data/cortex/Object.h"

namespace goon 
{
class RetinaMonitor
{    
public:    
   
private:
    static log4cxx::LoggerPtr logger;
    tron::Draw oDraw;

public:
//    RetinaMonitor();
//    ~RetinaMonitor();
    
    // Draws an image with the given list of regions 
    void drawRegions(cv::Mat& image_cam, std::list<Region>& listRegions);
    void drawObject(cv::Mat& image_cam, Object& oObject);
    
    cv::Mat& getOutput() {return (oDraw.getImage());};    

private:
    // obtains the border of a given mask
    //void getBorderMask (cv::Mat& mask, cv::Mat& mask_border);
};
}    
#endif
