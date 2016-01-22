/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "goon/data/visual_data.h"

namespace goon 
{
// Constructor
VisualData::VisualData ()
{    
    frame_num = 0;
}

// Destructor
VisualData::~VisualData ()
{
}

void VisualData::newFrame(cv::Mat image)
{
    std::lock_guard<std::mutex> lock(mutex_img);
    image_cam = image;
    frame_num++;
}

cv::Mat& VisualData::getImageCam()
{
    std::lock_guard<std::mutex> lock(mutex_img);
    return image_cam;    
}

int VisualData::getFrameNum()
{
    std::lock_guard<std::mutex> lock(mutex_img);
    return frame_num;
}

}


