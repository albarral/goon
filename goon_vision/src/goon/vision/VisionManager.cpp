/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "goon/vision/VisionManager.h"

namespace goon 
{
log4cxx::LoggerPtr VisionManager::logger(log4cxx::Logger::getLogger("goon.look"));

VisionManager::VisionManager() 
{
    blaunched = false;    
    workingCamera = goon::Grab::eCAM_WEBCAM;        
//    workingCamera = goon::Grab::eCAM_IPCAM;
//    workingCamera = goon::Grab::eVIDEO_CAMPUS_HALL;
//    workingCamera = goon::Grab::eIMAGE_CAMPUS_HALL1;
}

VisionManager::~VisionManager() 
{
}

bool VisionManager::launch(GoonBus& oGoonBus, VisualData& oVisualData, Capture& oCapture)
{      
    // launch it if not launched yet
    if (!blaunched)
    {
        log4cxx::NDC::push("VisionManager");   	
        LOG4CXX_INFO(logger, "Launching ");
        
        //float freq = pGoonConfig->getModulesFreq();
        float freq = 20.0; // TEMP to get from config

        // grab module (grabs images from camera)
        oGrab.init(oCapture, workingCamera);
        oGrab.setFrequency(freq);

        // see module (retinal & peripheral vision)
        oSee.init(oCapture, oVisualData, oGoonBus);
        oSee.setFrequency(freq);    

        // launch modules
        oGrab.on();
        oSee.on();    
        
        blaunched = true;    
    }
    // report problems
    else
        LOG4CXX_ERROR(logger, "Can't launch VisionManager: already launched!");        
    
    return blaunched;
}

void VisionManager::end()
{
    LOG4CXX_INFO(logger, "VisionManager: stopping modules ..."); 

    if (oSee.isOn())
    {    
        oSee.off();
        oSee.wait();
    }

    if (oGrab.isOn())
    {    
        oGrab.off();
        oGrab.wait();
    }

    LOG4CXX_INFO(logger, "VisionManager: finished");  
}

void VisionManager::oneShot(int testCamera, GoonBus& oGoonBus, VisualData& oVisualData, Capture& oCapture)
{
    LOG4CXX_INFO(logger, "VisionManager: one shot ..."); 
    
    oGrab.init(oCapture, testCamera);
    oGrab.setFrequency(30.0);
    oSee.init(oCapture, oVisualData, oGoonBus);
    
    oGrab.on();        
    oSee.oneShot();    
    oGrab.off();
    
    oGrab.wait();        
}

}
