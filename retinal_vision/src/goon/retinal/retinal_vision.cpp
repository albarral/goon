/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/imgproc/imgproc.hpp"          // for cvtColor

#include "goon/retinal/retinal_vision.h"
#include <goon/data/base/region.h>
#include <goon/utils/rgb_color.h>
#include <goon/utils/shape.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr RetinalVision::logger(Logger::getLogger("goon.retinal"));


RetinalVision::RetinalVision (Retina& oRetina) : mRetina(oRetina)
{
}

RetinalVision::~RetinalVision()
{
}


void RetinalVision::resize(int img_w, int img_h)
{
    oSegmentation.setSizes (img_w, img_h);
}


// This function changes main parameters of the retinal vision system.
void RetinalVision::setParameters (int retinal_samples, int same_RGB, int similar_RGB)
{
    oSegmentation.setNumSamples(retinal_samples);
    RGBColor::setTolerances(same_RGB, similar_RGB);
}


// This function performs the retinal vision process. 
// Detects homogenous color regions in the captured image (later used by higher vision processes).
void RetinalVision::update (cv::Mat& image_cam)
{
    LOG4CXX_TRACE(logger, "update - init");

    mRetina.clear();
    
    // convert to HSV space
    cv::Mat image_hsv;        
    cv::cvtColor(image_cam, image_hsv, CV_BGR2HSV);

    oSegmentation.extractRegions(image_cam, image_hsv, mRetina);

    //oMerge.doMerge(mRetina);

    mRetina.checkFinalRegions();

    LOG4CXX_DEBUG(logger, "regions = " << mRetina.getNumFinalRegions());
    LOG4CXX_TRACE(logger, "update - end");
}


void RetinalVision::computeCovariances()
{    
    LOG4CXX_TRACE(logger, "compute shapes");

    std::vector<int>::iterator it_region = mRetina.getFinalRegions().begin();
    std::vector<int>::iterator it_end = mRetina.getFinalRegions().end();
    // walk the list of final regions
    while (it_region != it_end)
    {
        Region& oRegion = mRetina.getRegion(*it_region);               
        
        Shape::computeCovariances(oRegion.getMask(), oRegion.getWindow(), oRegion.getPos(), oRegion.getCovariances());

        it_region++;
    }    
}

}
