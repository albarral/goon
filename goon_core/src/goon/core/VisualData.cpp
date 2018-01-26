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

void VisualData::updateRetina(Retina& oRetina)
{
    std::lock_guard<std::mutex> locker(mutexRetina);
    oRetina2.clear();
    oRetina2 = oRetina;    
}

void VisualData::updateROIs(Rois& oROIs)
{
    std::lock_guard<std::mutex> locker(mutexRois);
    oROIs2.clear();
    oROIs2 = oROIs;    
}

void VisualData::getRetinaCopy(Retina& oRetina3)
{
    std::lock_guard<std::mutex> locker(mutexRetina);
    oRetina3.clear();
    oRetina3 = oRetina2;        
}

void VisualData::getROIsCopy(Rois& oROIs3)
{
    std::lock_guard<std::mutex> locker(mutexRois);
    oROIs3.clear();
    oROIs3 = oROIs2;        
}

void VisualData::cloneObject(Object& oObject)
{
    std::lock_guard<std::mutex> locker(mutexObject);
    oObject2 = oObject;    
}

//Retina& VisualData::getRetina2()
//{
//    std::lock_guard<std::mutex> locker(mutexRetina);
//    return oRetina2;    
//}  
//
//Rois& VisualData::getROIs2()
//{
//    std::lock_guard<std::mutex> locker(mutexRois);
//    return oROIs2;    
//}

Object& VisualData::getObject2()
{
    std::lock_guard<std::mutex> locker(mutexObject);
    return oObject2;
}
}

