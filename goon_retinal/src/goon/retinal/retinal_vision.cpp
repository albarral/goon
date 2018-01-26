/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/imgproc/imgproc.hpp"          // for cvtColor

#include "goon/retinal/retinal_vision.h"
#include <goon/data/base/region.h>
#include <goon/features/color/rgb_color.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr RetinalVision::logger(Logger::getLogger("goon.retinal"));

RetinalVision::RetinalVision()
{  
}

RetinalVision::~RetinalVision()
{
}

void RetinalVision::init(int img_w, int img_h)
{
    oSegmentation4.init(oRetina, img_w, img_h);
    oMerge.init(img_w, img_h);
}

// This function changes main parameters of the retinal vision system.
void RetinalVision::setParameters (int retinal_samples, int same_RGB, int similar_RGB)
{
    oSegmentation4.setNumSamples(retinal_samples);
    RGBColor::setTolerances(same_RGB, similar_RGB);
}


// This function performs the retinal vision process. 
// Detects homogenous color regions in the captured image (later used by higher vision processes).
void RetinalVision::update (cv::Mat& image_cam)
{
    LOG4CXX_TRACE(logger, "update - init");

    // clear retina on every update
    oRetina.clear();
    
    // convert to HSV space
    cv::Mat image_hsv;        
    cv::cvtColor(image_cam, image_hsv, CV_BGR2HSV);

    oSegmentation4.extractRegions(image_cam, image_hsv);
    
    // show retina description
    LOG4CXX_DEBUG(logger, oRetina.shortDesc());
//    cv::Vec3b hsvColor(8, 230, 180); 
//    cv::Vec3b hsvDev(3, 30, 60); 
//    LOG4CXX_DEBUG(logger, oRetina.showFilterByColor(hsvColor, hsvDev));

    oMerge.doMerge(oRetina);

    LOG4CXX_TRACE(logger, "update - end");
}


void RetinalVision::computeCovariances()
{    
    LOG4CXX_TRACE(logger, "computeCovariances - init");

    // walk the list of final regions
    for (Region& oRegion : oRetina.getListRegions())
    {
        LOG4CXX_TRACE(logger, "region = " << oRegion.toString());
        oRegion.computeBasicShape();
    }    
    
    LOG4CXX_TRACE(logger, "computeCovariances - end");
}

void RetinalVision::describeRegions()
{
    LOG4CXX_DEBUG(logger, "regions description ...");
    for (Region& oRegion : oRetina.getListRegions()) 
    {
        LOG4CXX_DEBUG(logger, oRegion.shortDesc());
    } 
}

}
