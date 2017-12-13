#ifndef __GOON_GRABBER_H
#define __GOON_GRABBER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include <opencv2/opencv.hpp>
#include "goon/camera/camera.h"

namespace goon
{    
// Class used to grab images from different types of camera, videos or static images.
class Grabber 
{
private:
    static log4cxx::LoggerPtr logger;
    bool bconnected;
    Camera* pCamera;        // pointer to connected camera
    int counter;        // frame counter
    
public:
    Grabber();
    ~Grabber();
        
    bool isReady() {return bconnected;}
    
    bool connect2Webcam();    
    bool connect2IPCam(std::string ipAddress);
    bool connect2Video(std::string filePath);
    bool connect2Image(std::string filePath);
    
    // grabs image from camera 
    bool grab();        
    int getCounter() {return counter;}
    // get pointer to captured image
    cv::Mat& getCapture();

    
private:
    // checks if given file path exists
    bool checkFileExists(std::string filePath);
    // tries connection with camera
    bool tryConnection();
};

}
#endif
