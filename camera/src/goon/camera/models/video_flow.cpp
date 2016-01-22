/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/camera/models/video_flow.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr VideoFlow::logger(Logger::getLogger("goon.camera"));

VideoFlow::VideoFlow (std::string path)
{
   address = path;    
}

VideoFlow::~VideoFlow()
{
}


int VideoFlow::connect() 
{
    int ret = 0;
    
    //open the video stream and make sure it's opened
    if (vCapture.open(address))         
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


int VideoFlow::grab() 
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