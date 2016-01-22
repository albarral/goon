#ifndef __GOON_WEB_CAMERA_H
#define __GOON_WEB_CAMERA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>            
#include <log4cxx/logger.h>

#include "goon/camera/camera.h"

namespace goon 
{
// This class implements the image capture process in webcams.
// It extends from Camera.
class WebCamera : public Camera
{
private:
    static log4cxx::LoggerPtr logger;
    cv::VideoCapture vCapture;
    int device_id;

public:
    // The index of the camera must be specified. 
    WebCamera (int index = 0);
    ~WebCamera();

    // connects to the camera 
    int connect();

    // capture new frame
    int grab();    
};
}
	
#endif
	
