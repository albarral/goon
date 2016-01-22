/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "goon/camera/models/ip_camera.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr ipCamera::logger(Logger::getLogger("goon.camera"));

ipCamera::ipCamera (std::string saddress)
{
   address = saddress;    
}


ipCamera::~ipCamera()
{
}


int ipCamera::connect() 
{
    int ret = 0;
    
    LOG4CXX_INFO(logger, "connect to camera ... " << address);
    
    //open the video stream and make sure it's opened
    if (vCapture.open(address))         
    {        
        bconnected = true;
        LOG4CXX_INFO(logger, "connected");

        if (vCapture.read(image))
        {
            img_w = image.cols;
            img_h = image.rows;            
        }
        LOG4CXX_INFO(logger, "capture size = " << img_w << "x" << img_h);
        
        //flush(time_connect);
    }
    else
    {
        ret = -1;
        LOG4CXX_ERROR(logger, "connection failed - " << address);
    }

    return ret;
}


int ipCamera::grab() 
{
    int ret = 0;

    if (vCapture.read(image)) 
    {
        LOG4CXX_INFO(logger, "frame " << counter);
    }
    else 
    {
        ret = -1;
        LOG4CXX_ERROR(logger, "grab error!");
    }
        
    counter ++;
    return ret;
}

/*
int ipCamera::flush(int ms_connect) 
{
    int ret = 0;

    int cam_fps = vCapture.get(CV_CAP_PROP_FPS);    
    LOG4CXX_TRACE(logger, "camera fps (read) = " << cam_fps);
    // IMPORTANT: a wrong fps (25) is read from Wifibot's IP camera -> manually set to 5
    cam_fps = 5;
    LOG4CXX_TRACE(logger, "camera fps (real) = " << cam_fps);
    int num_frames = cam_fps * ms_connect / 1000;
    
    for (int i=0; i<num_frames; i++)
    {
        if (vCapture.read(image)) 
        {
            LOG4CXX_TRACE(logger, "flush " << counter);
        }
        else 
        {
            ret = -1;
            LOG4CXX_ERROR(logger, "flush error!");
        }
        counter ++;        
    }
        
    return ret;
}
 */ 
}