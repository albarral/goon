/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/show/monitor/ROIsMonitor.h"
#include <goon/features/shape/shape.h>
#include <maty/math/Coordinates.h>

using namespace log4cxx;

namespace goon 
{
LoggerPtr ROIsMonitor::logger(Logger::getLogger("goon.show"));

// Shows an image with the ROIs obtained by the peripheral vision process.
void ROIsMonitor::drawRois(cv::Mat& image_cam, std::list<ROI>& listROIs)
{
    float roi_w, roi_h, roi_angle;      // ellipse values
    cv::Vec3f covs;

    std::list<ROI>::iterator it_roi = listROIs.begin();
    std::list<ROI>::iterator it_end = listROIs.end();

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
        int color = tivy::Draw::eYELLOW;
        
        float* speed = it_roi->getMotion().getSpeed();
        float absSpeed, angle;
        maty::Coordinates::cartesian2polar(speed[0], speed[1], absSpeed, angle);
        // speed > 0.1 pixels/ms (100 pixels/s))
        if (absSpeed > 0.01)
        {
            color = tivy::Draw::eRED;            
        }
        oDraw.drawPoint(centroid, color, it_roi->getStability());
        //oDrawPer.drawNumber(it_roi->getID(), centroid);                        
        
        it_roi++;
    }    
}

void ROIsMonitor::drawFPS(float fps)
{
    cv::Point point(10, 20);
    oDraw.setDefaultColor(tivy::Draw::eGREEN);    
    oDraw.drawFloatNumber(fps, point);     
}
}