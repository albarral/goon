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
    
    // Shows an image with the ROIs obtained by the peripheral vision process.
    void draw (cv::Mat& image_cam, std::vector<ROI>& listROIs);

    cv::Mat& getOutput() {return (oDraw.getOutput());};        
};
}    
#endif
