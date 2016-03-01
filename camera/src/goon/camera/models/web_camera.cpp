/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/camera/models/web_camera.h"

namespace goon 
{
WebCamera::WebCamera (int index)
{
    type = Camera::eCAM_WEBCAM;
   device_id = index;    
   address = "dev/video" + std::to_string(index);
}

WebCamera::~WebCamera()
{
}

bool WebCamera::connect() 
{
    //open the video stream and make sure it's opened
    if (vCapture.open(device_id))         
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

bool WebCamera::grab() 
{
    return (vCapture.read(image));
}

}