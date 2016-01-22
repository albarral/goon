/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "camera.h"

namespace goon 
{
Camera::Camera ()
{
   address = "";    
   bconnected = false;
   visualField = 0;
   img_w = 0;
   img_h = 0;
   height = 0;
   counter = 0;
}


void Camera::getCaptureCopy(cv::Mat* image_dest)
{
    image.copyTo(*image_dest);
}
}