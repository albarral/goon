/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "goon/vision/modules/Grab.h"

namespace goon
{    
log4cxx::LoggerPtr Grab::logger(log4cxx::Logger::getLogger("goon.vision.grab"));

Grab::Grab() 
{  
    modName = "Grab";
}

//Grab::~Grab() 
//{
//}

void Grab::showInitialized()
{
    LOG4CXX_INFO(logger, modName + " initialized");             
};

bool Grab::setCameraSource(int sourceCamera)
{
    // camera object instantiation
    connect2Camera(sourceCamera);

    if (oGrabber.isReady())
    {
        LOG4CXX_INFO(logger, "Grab initialized");   
        return true;
    }
    else
    {
        LOG4CXX_ERROR(logger, "FAILED Grab initialization!");    
        return false;
    }    
};


void Grab::first()
{    
    log4cxx::NDC::push("Grab");   	
    
    if (oGrabber.isReady())
    {
        LOG4CXX_INFO(logger, "started");  
        setState(Grab::eSTATE_ON);
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "Grabber not connected to camera. Going off ... ");  
        tuly::Module3::off();        
    }
}

void Grab::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void Grab::loop()
{   
    // grab image & pass it to the vision system
    if (oGrabber.grab())            
    {
        pVisualData->setCameraFrame(oGrabber.getCapture());
        // produce new beat
        newBeat();
        // SO
        pGoonBus->getSO_GRAB_BEAT().setValue(beat);
    }
}

void Grab::connect2Camera(int option)
{
    switch (option)
    {
        case Grab::eCAM_WEBCAM:  
            oGrabber.connect2Webcam();
            //oGrabber.setVisualField(33);       
            LOG4CXX_INFO(logger, "Web camera");
            break;

        case Grab::eCAM_IPCAM:                        
            oGrabber.connect2IPCam("http://192.168.1.3/video.cgi?.mjpg");
            //oGrabber.setVisualField(33);                
            //oGrabber.setCamHeight(25);
            LOG4CXX_INFO(logger, "IP camera");
            break;
            
        case Grab::eCAM_WIFIBOT_WIRELESS:            
            oGrabber.connect2IPCam("http://192.168.1.105/video.cgi?.mjpg");
            //oGrabber.setVisualField(33);                
            //oGrabber.setCamHeight(25);
            LOG4CXX_INFO(logger, "IP camera: Wifibot (wireless)");
            break;

        case Grab::eCAM_ALBARRACIN:
            oGrabber.connect2IPCam("http://212.170.22.153:8080/mjpg/video.mjpg");
            LOG4CXX_INFO(logger, "IP camera: webcam Albarracin");
            break;

        case Grab::eCAM_SOUTHERN_BEACH:
            oGrabber.connect2IPCam("http://66.184.211.231/mjpg/video.mjpg");
            LOG4CXX_INFO(logger, "IP camera: webcam Southernmost beach");
            break;
            
        case Grab::eVIDEO_CAMPUS_HALL:
            oGrabber.connect2Video("/home/albarral/PROJECTS/IMAGES/sequences/campus_hall.MP4");
            LOG4CXX_INFO(logger, "Video: campus hall");
            break;
            
        case Grab::eIMAGE_CAMPUS_HALL1:
            oGrabber.connect2Image("/home/albarral/TESTS/images/campus_hall1.png");
            LOG4CXX_INFO(logger, "Image: campus hall 1");
            break;
            
        case Grab::eIMAGE_CAMPUS_HALL2:
            oGrabber.connect2Image("/home/albarral/TESTS/images/campus_hall2.png");
            LOG4CXX_INFO(logger, "Image: campus hall 2");
            break;

        case Grab::eIMAGE_CAMPUS_HALL3:
            oGrabber.connect2Image("/home/albarral/TESTS/images/campus_hall3.png");
            LOG4CXX_INFO(logger, "Image: campus hall 3");
            break;

        case Grab::eIMAGE_CAMPUS_HALL4:
            oGrabber.connect2Image("/home/albarral/TESTS/images/campus_hall4.png");
            LOG4CXX_INFO(logger, "Image: campus hall 4");
            break;

        case Grab::eIMAGE_BABOON:
            oGrabber.connect2Image("/home/albarral/TESTS/images/baboon.jpg");
            LOG4CXX_INFO(logger, "Image: babbon");
            break;

        case Grab::eIMAGE_FRUITS:
            oGrabber.connect2Image("/home/albarral/TESTS/images/fruits.jpg");
            LOG4CXX_INFO(logger, "Image: fruits");
            break;

        case Grab::eIMAGE_JLUIS:
            oGrabber.connect2Image("/home/albarral/TESTS/images/jluis.jpg");
            LOG4CXX_INFO(logger, "Image: jluis");
            break;

        case Grab::eIMAGE_ORANGE1:
            oGrabber.connect2Image("/home/albarral/TESTS/images/image_orange1.jpg");
            LOG4CXX_INFO(logger, "Image: orange1");
            break;
            
        case Grab::eIMAGE_ORANGE2:
            oGrabber.connect2Image("/home/albarral/TESTS/images/image_orange2.jpg");
            LOG4CXX_INFO(logger, "Image: orange2");
            break;
    }
}

}