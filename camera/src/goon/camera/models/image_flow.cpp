/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/highgui/highgui.hpp"  // for imread

#include "goon/camera/models/image_flow.h"

namespace goon 
{
ImageFlow::ImageFlow (std::string path)
{                
    type = Camera::eCAM_IMAGE;
    address = path;    
    bread = false;
}

ImageFlow::~ImageFlow()
{
}


bool ImageFlow::connect() 
{
    image = cv::imread(address);

    if (image.data != NULL) 
    {
        bread = true;
        img_w = image.cols;       
        img_h = image.rows;            
        return true;
    }
    else
        return false;
}


bool ImageFlow::grab() 
{
    // just need to read it once, in connect function
    if (!bread) 
    {
        image = cv::imread(address);
    }
    return true;
}
}