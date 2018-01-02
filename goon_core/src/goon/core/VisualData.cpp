/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "goon/core/VisualData.h"

namespace goon 
{
// Constructor
VisualData::VisualData ()
{    
}

// Destructor
VisualData::~VisualData ()
{
}

void VisualData::setCameraFrame(cv::Mat& img)
{
    std::lock_guard<std::mutex> lock(mutexCam);
    // makes copy of given image
    img.copyTo(imageCam);
}

void VisualData::getCameraFrameCopy(cv::Mat& imageOut)
{
    std::lock_guard<std::mutex> lock(mutexCam);
    // takes copy of cam image
    imageCam.copyTo(imageOut);    
}

void VisualData::cloneRetina()
{
    std::lock_guard<std::mutex> locker(mutexRetina);
    // clone retina
    oRetina2 = oRetina;    
}

void VisualData::cloneROIs()
{
    std::lock_guard<std::mutex> locker(mutexRois);
    // clone ROIS 
    oROIs2 = oROIs;    
}

Retina& VisualData::getRetina2()
{
    std::lock_guard<std::mutex> locker(mutexRetina);
    return oRetina2;    
}  

Rois& VisualData::getROIs2()
{
    std::lock_guard<std::mutex> locker(mutexRois);
    return oROIs2;    
}

}

