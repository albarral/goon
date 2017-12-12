#ifndef __GOON_WEB_CAMERA_H
#define __GOON_WEB_CAMERA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>            

#include "goon/camera/camera.h"

namespace goon 
{
// This class implements the image capture process in webcams.
// It extends from Camera.
class WebCamera : public Camera
{
private:
    cv::VideoCapture vCapture;
    int device_id;

public:
    // The index of the camera must be specified. 
    WebCamera (int index = 0);
    ~WebCamera();

    // connect to camera 
    virtual bool connect();
    // capture new frame
    virtual bool grab();
};
}
	
#endif
	
