/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/capture.h"

namespace goon 
{
// Constructor
Capture::Capture ()
{    
    frameNum = 0;
}

// Destructor
Capture::~Capture ()
{
}

void Capture::newFrame(cv::Mat& img)
{
    std::lock_guard<std::mutex> lock(mutex);
    // takes a copy of the given image
    img.copyTo(image);
    frameNum++;
}

cv::Mat& Capture::getImage()
{
    std::lock_guard<std::mutex> lock(mutex);
    return image;    
}

void Capture::getImageCopy(cv::Mat& imageOut)
{
    std::lock_guard<std::mutex> lock(mutex);
    // takes a copy of the given image
    image.copyTo(imageOut);    
}

int Capture::getFrameNum()
{
    std::lock_guard<std::mutex> lock(mutex);
    return frameNum;
}

}


