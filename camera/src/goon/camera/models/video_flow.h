#ifndef __GOON_VIDEO_FLOW_H
#define __FOON_VIDEO_FLOW_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/opencv.hpp>
#include <log4cxx/logger.h>

#include "goon/camera/camera.h"

namespace goon 
{
// This class implements the image capture process from recorded videos.
// It extends from Camera.
class VideoFlow : public Camera
{
private:
    static log4cxx::LoggerPtr logger;
    cv::VideoCapture vCapture;

public:
    VideoFlow (std::string path);
    ~VideoFlow();

    // connects to the video file
    int connect();

    // capture new frame
    int grab();
};
}	
#endif
	
