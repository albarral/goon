/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <fstream>

#include "goon/camera/Grabber.h"
#include "goon/camera/models/web_camera.h"
#include "goon/camera/models/ip_camera.h"
#include "goon/camera/models/video_flow.h"
#include "goon/camera/models/image_flow.h"

namespace goon
{    
log4cxx::LoggerPtr Grabber::logger(log4cxx::Logger::getLogger("goon.grabber"));

Grabber::Grabber() 
{
    binitialized = false;
    pCamera = 0;
    pCapture = 0;
    counter = 0;
}

Grabber::~Grabber() 
{
    if (pCamera != 0)
        delete (pCamera);
}

void Grabber::init(Capture& oCapture)
{
    // get shared visual data
    pCapture = &oCapture;
    binitialized = true;
};

 bool Grabber::connect2Webcam()
 {     
    LOG4CXX_INFO(logger, "Grabber: connecting to webcam ...");
    
    pCamera = new WebCamera(0);              
    if (pCamera != 0)
        return tryConnection();
    else
    {
        LOG4CXX_ERROR(logger, "Failed WebCamera creation");
        return false;
    }
}
    
 bool Grabber::connect2IPCam(std::string ipAddress)
 {
    LOG4CXX_INFO(logger, "Grabber: connecting to IP camera ...");
    
    pCamera = new ipCamera(ipAddress);
    if (pCamera != 0)
        return tryConnection();
    else
    {
        LOG4CXX_ERROR(logger, "Failed ipCamera creation");
        return false;
    }
 }
    
bool Grabber::connect2Video(std::string filePath)
{
    LOG4CXX_INFO(logger, "Grabber: connecting to video ...");
    
    if (!checkFileExists(filePath))
    {
        LOG4CXX_ERROR(logger, "File does not exist - " << filePath);
        return false;
    }
    
    pCamera = new VideoFlow(filePath);
    if (pCamera != 0)
        return tryConnection();
    else
    {
        LOG4CXX_ERROR(logger, "Failed VideoFlow creation");
        return false;
    }
}
    
bool Grabber::connect2Image(std::string filePath)
{
    LOG4CXX_INFO(logger, "Grabber: connecting to image ...");

    if (!checkFileExists(filePath))
    {
        LOG4CXX_ERROR(logger, "File does not exist - " << filePath);
        return false;
    }

    pCamera = new ImageFlow(filePath);
    if (pCamera != 0)
        return tryConnection();
    else
    {
        LOG4CXX_ERROR(logger, "Failed ImageFlow creation");
        return false;
    }
}

void Grabber::grab()
{   
    // grab image & pass it to the vision system
    if (pCamera->grab())
    {
        counter++;      
        pCapture->newFrame(pCamera->getCapture());
        LOG4CXX_TRACE(logger, "frame " << counter);
    }  
    else
        LOG4CXX_ERROR(logger, "grab error!");        
}

bool Grabber::checkFileExists(std::string filePath)
{
    std::ifstream inFile(filePath);
        
    // file exists
    if (inFile)
        return true;
    // file not exists
    else
        return false;
}

bool Grabber::tryConnection()
{
    if (pCamera->connect())
    {
        bconnected = true;
        LOG4CXX_INFO(logger, "connected ok");
        LOG4CXX_INFO(logger, "capture size = " << pCamera->getImgWidth() << "x" << pCamera->getImgHeight());
    }
    else
    {
        bconnected = false;
        LOG4CXX_ERROR(logger, "connection failed");    
    }    
    return bconnected;
}

}