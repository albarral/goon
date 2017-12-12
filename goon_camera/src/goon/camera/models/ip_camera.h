#ifndef __GOON_IP_CAMERA_H
#define __GOON_IP_CAMERA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/highgui/highgui.hpp>            

#include "goon/camera/camera.h"

namespace goon 
{
// This class implements the image capture process in IP cameras.
// It extends from Camera.
class ipCamera : public Camera
{
private:
    cv::VideoCapture vCapture;

public:
    ipCamera (std::string saddress);
    ~ipCamera();

    // connect to camera 
    virtual bool connect();
    // capture new frame
    virtual bool grab();
    
    private:
        // empties the video capture buffer that was filled during the specified connecting time (in ms)
  //      int flush(int ms_connect);
};
}
	
#endif
	
