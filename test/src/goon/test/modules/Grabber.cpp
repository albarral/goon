/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "goon/test/modules/Grabber.h"
#include "goon/test/camera_factory.h"

namespace goon
{    
log4cxx::LoggerPtr Grabber::logger(log4cxx::Logger::getLogger("goon.test"));

Grabber::Grabber() 
{
    //  initial state must be Module::state_OFF
    binitialized = false;
    oCamera = 0;
    pVisualData = 0;
}

Grabber::~Grabber() 
{
    if (oCamera != 0)
        delete (oCamera);
}

void Grabber::init(VisualData& oVisualData, int workingCamera)
{
    // get shared visual data
    pVisualData = &oVisualData;
    // camera object instantiation
    oCamera = CameraFactory::createCamera(workingCamera);    
    if (oCamera->connect() == 0)
    {
        binitialized = true;
        LOG4CXX_INFO(logger, "Grabber initialized");             
    }
    else
    {
        binitialized = false;
        LOG4CXX_ERROR(logger, "FAILED Grabber initialization!");    
    }    
};


void Grabber::first()
{    
    log4cxx::NDC::push("grabber");   	
    
    if (binitialized)
    {
        LOG4CXX_INFO(logger, "started");  
        setState(Grabber::eSTATE_ON);
        setPrevState(Module::state_OFF);
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized. Going off ... ");  
        Module::off();        
    }
}

void Grabber::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void Grabber::loop()
{   
    // grab image & pass it to the vision system
    oCamera->grab();        
    pVisualData->newFrame(oCamera->getCapture());
}

}