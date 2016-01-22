/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/camera/models/web_camera.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr WebCamera::logger(Logger::getLogger("goon.camera"));

WebCamera::WebCamera (int index)
{
   device_id = index;    
   address = "dev/video" + std::to_string(index);
}

WebCamera::~WebCamera()
{
}

int WebCamera::connect() 
{
    int ret = 0;
    
    //open the video stream and make sure it's opened
    if (vCapture.open(device_id))         
    {
        
        bconnected = true;
        LOG4CXX_INFO(logger, "connection ok - " << address);

        if (vCapture.read(image))
        {
            img_w = image.cols;
            img_h = image.rows;            
        }
        LOG4CXX_INFO(logger, "capture size = " << img_w << "x" << img_h);
    }
    else
    {
        ret = -1;
        LOG4CXX_ERROR(logger, "connection failed - " << address);
    }

    return ret;
}


int WebCamera::grab() 
{
    int ret = 0;

    if (vCapture.read(image)) 
    {
        LOG4CXX_TRACE(logger, "frame " << counter);
    }
    else 
    {
        ret = -1;
        LOG4CXX_ERROR(logger, "grab error!");
    }
        
    counter ++;
    return ret;
}
}