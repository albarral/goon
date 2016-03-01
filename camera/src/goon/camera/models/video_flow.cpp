/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/camera/models/video_flow.h"

namespace goon 
{
VideoFlow::VideoFlow (std::string path)
{       
    type = Camera::eCAM_VIDEO;
   address = path;    
}

VideoFlow::~VideoFlow()
{
}


bool VideoFlow::connect() 
{
    //open the video stream and make sure it's opened
    if (vCapture.open(address))         
    {
        if (vCapture.read(image))
        {
            img_w = image.cols;
            img_h = image.rows;            
        }
        return true;
    }
    else
        return false;
}


bool VideoFlow::grab() 
{
    return (vCapture.read(image));
}

}