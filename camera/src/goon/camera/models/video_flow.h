#ifndef __GOON_VIDEO_FLOW_H
#define __FOON_VIDEO_FLOW_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/opencv.hpp>

#include "goon/camera/camera.h"

namespace goon 
{
// This class implements the image capture process from recorded videos.
// It extends from Camera.
class VideoFlow : public Camera
{
private:
    cv::VideoCapture vCapture;

public:
    VideoFlow (std::string path);
    ~VideoFlow();

    // connect to camera 
    virtual bool connect();
    // capture new frame
    virtual bool grab();
};
}	
#endif
	
