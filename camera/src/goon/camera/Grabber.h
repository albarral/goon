#ifndef __GOON_GRABBER_H
#define __GOON_GRABBER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "goon/camera/camera.h"
#include "goon/data/capture.h"

namespace goon
{    
// Class used to grab images from different types of camera, videos or static images.
class Grabber 
{
private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    bool bconnected;
    Camera* pCamera;        // pointer to connected camera
    Capture* pCapture;        // shared data
    int counter;        // frame counter
    
public:
    Grabber();
    ~Grabber();
    
    // initializes the module 
    void init(Capture& oCapture);   
    
    bool isReady() {return binitialized & bconnected;}
    
    bool connect2Webcam();    
    bool connect2IPCam(std::string ipAddress);
    bool connect2Video(std::string filePath);
    bool connect2Image(std::string filePath);
    
    // grabs image from camera & stores it in the Capture object (for sharing it)
    void grab();    
    int getCounter() {return counter;}
    
private:
    // checks if given file path exists
    bool checkFileExists(std::string filePath);
    // tries connection with camera
    bool tryConnection();
};

}
#endif
