/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep
#include "log4cxx/ndc.h"

#include "goon/vision/modules/See.h"
#include "goon/data/retina.h"
#include "goon/data/rois.h"

namespace goon
{    
log4cxx::LoggerPtr See::logger(log4cxx::Logger::getLogger("goon.vision.see"));

See::See() 
{
    modName = "See";
}
  
void See::showInitialized()
{
    LOG4CXX_INFO(logger, modName + " initialized");             
};

void See::first()
{    
    log4cxx::NDC::push("See");   	
    
    // we start in LOST state
    if (benabled)
    {
        LOG4CXX_INFO(logger, "started");  
        setState(See::eSTATE_ON);
        
        // connect led to Grab beat sensor
        oGrabBeatLed.init(pGoonBus->getSO_GRAB_BEAT());
        wait4GrabBeat();
        // set sizes for retinal vision
        pVisualData->getCameraFrameCopy(imageCam);
        LOG4CXX_INFO(logger, "IMAGE SIZE " << imageCam.cols << "x" << imageCam.rows);    
        oRetinalVision.init(imageCam.cols, imageCam.rows); // w, h
        oClick.start();
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized Going off ... ");  
        tron::Module3::off();        
    }
}

void See::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void See::loop()
{   
    // if grab beat not changed, skip
    if (!oGrabBeatLed.check())
        return;
        
    // get camera capture 
    pVisualData->getCameraFrameCopy(imageCam);            

    // clock measure
    oClick.read();    
    oClick.start();

    // processes it 
    LOG4CXX_DEBUG(logger, "retinal ... ");
    oRetinalVision.update(imageCam);    
    Retina& oRetina = oRetinalVision.getRetina();
    
    LOG4CXX_DEBUG(logger, "peripheral ... ");
    oPeripheralVision.update(oRetina, oClick.getMillis());    
    Rois& oROIs = oPeripheralVision.getROIs();
    
    // stores dynamic visual data into static one 
    LOG4CXX_TRACE(logger, "clone retina ... ");
    pVisualData->updateRetina2(oRetina);
    LOG4CXX_TRACE(logger, "clone ROIS ... ");
    pVisualData->updateROIs2(oROIs);

    // measure processing speed
    fps = 1000.0/oClick.getMillis();
    
    // produce new beat
    newBeat();
    writeBus();    
}

void See::writeBus()
{
    pGoonBus->getSO_SEE_FPS().setValue(fps);
    pGoonBus->getSO_SEE_BEAT().setValue(beat);
}

void See::wait4GrabBeat()
{
    LOG4CXX_INFO(logger, "wait first grab beat");     
    // wait while Grab beat not changed
    while (!oGrabBeatLed.check())            
        usleep(50000);  // 50 ms
}

// just one loop execution (for testing)
void See::oneShot()
{
    first();
    loop();
    bye();
}

}