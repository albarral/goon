/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/monitor/ROIsMonitor.h"
#include <goon/utils/shape.h>

using namespace log4cxx;

namespace goon 
{
LoggerPtr ROIsMonitor::logger(Logger::getLogger("goon.monitor"));

// Shows an image with the ROIs obtained by the peripheral vision process.
void ROIsMonitor::drawRois(cv::Mat& image_cam, std::vector<ROI>& listROIs)
{
    float roi_w, roi_h, roi_angle;      // ellipse values
    cv::Vec3f covs;

    std::vector<ROI>::iterator it_roi = listROIs.begin();
    std::vector<ROI>::iterator it_end = listROIs.end();

    oDraw.setBackGround(image_cam);
    
    // walk the list of rois (all are valid)
    while (it_roi != it_end)
    {
        // computes main ellipse
        covs = it_roi->getCovariances();     // cxx, cyy, cxy        
        Shape::computeEllipse(covs[0], covs[1], covs[2], roi_w, roi_h, roi_angle);            
        int* pos = it_roi->getPos();
        cv::Point centroid(pos[0], pos[1]);                  

        LOG4CXX_TRACE(logger, "roi " << it_roi->getID());        
        LOG4CXX_TRACE(logger, "(w, h, angle) = " << roi_w << ", " << roi_h << ", " << roi_angle);        
        oDraw.drawEllipse(centroid, roi_w, roi_h, -roi_angle);
        oDraw.drawPoint(centroid, Draw::eYELLOW, it_roi->getStability());
        //oDrawPer.drawNumber(it_roi->getID(), centroid);                        
        
        it_roi++;
    }    
}

void ROIsMonitor::drawFPS(float fps)
{
    cv::Point point(10, 20);
    oDraw.setDefaultColor(Draw::eGREEN);    
    oDraw.drawFloatNumber(fps, point);     
}
}