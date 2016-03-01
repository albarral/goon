/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "goon/camera/models/ip_camera.h"

namespace goon 
{
ipCamera::ipCamera (std::string saddress)
{
    type = Camera::eCAM_IPCAM;
   address = saddress;    
}


ipCamera::~ipCamera()
{
}


bool ipCamera::connect() 
{
    //open the video stream and make sure it's opened
    if (vCapture.open(address))         
    {        
        if (vCapture.read(image))
        {
            img_w = image.cols;
            img_h = image.rows;            
        }
        //flush(time_connect);
        return true;        
    }
    else
        return false;
}


bool ipCamera::grab() 
{
    return (vCapture.read(image));
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