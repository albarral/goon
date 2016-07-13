/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "goon/look/LookManager.h"

namespace goon 
{
log4cxx::LoggerPtr LookManager::logger(log4cxx::Logger::getLogger("goon.look"));

LookManager::LookManager() 
{
      workingCamera = goon::Grab::eCAM_WEBCAM;        
//    workingCamera = goon::Grab::eCAM_IPCAM;
//    workingCamera = goon::Grab::eVIDEO_CAMPUS_HALL;
//    workingCamera = goon::Grab::eIMAGE_CAMPUS_HALL1;
}

LookManager::~LookManager() 
{
}

void LookManager::startModules()
{ 
    LOG4CXX_INFO(logger, "LookManager: starting modules ..."); 

    // grab module (grabs images from camera)
    oGrab.init(oCapture, workingCamera);
    oGrab.setFrequency(30.0);

    // see module (retinal & peripheral vision)
    oSee.init(oCapture, oVisualData, oLookBus);
    oSee.setFrequency(20.0);    // to just wait 50ms among loops

    // monitoring module (shows output of the process)
    oLookMonitor.init(oCapture, oVisualData, oLookBus); 
    oLookMonitor.setFrequency(30.0);

    // launch modules
    oGrab.on();
    oSee.on();    
    oLookMonitor.on();

    sleep(1);    
    if (oGrab.isOff() || oSee.isOff() || oLookMonitor.isOff())
    {      
        LOG4CXX_ERROR(logger, "LookManager: start failed!");
    }
    else
    {
        LOG4CXX_INFO(logger, "LookManager: started ok");  
    }
}

void LookManager::stopModules()
{
    LOG4CXX_INFO(logger, "LookManager: stopping modules ..."); 

    if (!oLookMonitor.isOff())
    {
        oLookMonitor.off();
        oLookMonitor.wait();
    }

    if (!oSee.isOff())
    {    
        oSee.off();
        oSee.wait();
    }

    if (!oGrab.isOff())
    {    
        oGrab.off();
        oGrab.wait();
    }

    LOG4CXX_INFO(logger, "LookManager: finished");  
}

void LookManager::oneShot(int testCamera)
{
    LOG4CXX_INFO(logger, "LookManager: one shot ..."); 
    
    oGrab.init(oCapture, workingCamera);
    oGrab.setFrequency(30.0);
    oSee.init(oCapture, oVisualData, oLookBus);
    
    oGrab.on();        
    oSee.oneShot();    
    oGrab.off();
    
    oGrab.wait();        
}

}
