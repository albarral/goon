/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "goon/vision/modules/See.h"

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
        
        // set sizes for retinal vision
        wait4FirstCapture();
        pVisualData->getImageCopy(imageCam);
        LOG4CXX_INFO(logger, "IMAGE SIZE " << imageCam.cols << "x" << imageCam.rows);    
        oRetinalVision.init(pVisualData->getRetina(), imageCam.cols, imageCam.rows); // w, h
        oPeripheralVision.init(pVisualData->getRetina(), pVisualData->getROIs());
        oClick.start();
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized Going off ... ");  
        tuly::Module3::off();        
    }
}

void See::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void See::loop()
{   
    // get last camera capture (don't need to wait, grab is much faster than see)
    pVisualData->getImageCopy(imageCam);            
    // processes it 
    LOG4CXX_DEBUG(logger, "retinal ... ");
    oRetinalVision.update(imageCam);    
    oRetinalVision.computeCovariances();         
    LOG4CXX_DEBUG(logger, "peripheral ... ");
    oPeripheralVision.update();    
    
    // stores dynamic visual data into static one 
    LOG4CXX_TRACE(logger, "clone retina ... ");
    pVisualData->storeRetinaPhoto();
    LOG4CXX_TRACE(logger, "clone ROIS ... ");
    pVisualData->storeROIsPhoto();

    // measure processing speed
    oClick.read();    
    oClick.start();
    fps = 1000.0/oClick.getMillis();
    // produce new beat
    newBeat();
    
    // write bus - SO
    pGoonBus->getSO_SEE_BEAT().setValue(beat);
    pGoonBus->getSO_SEE_FPS().setValue(fps);
}

void See::wait4FirstCapture()
{
    LOG4CXX_INFO(logger, "waiting for first image");     
    // wait for new grabbed frame (50ms waits)
    while (pGoonBus->getSO_GRAB_BEAT().getValue() == 0)            
        usleep(50000);
}

// just one loop exectution (for testing)
void See::oneShot()
{
    first();
    loop();
    bye();
}

}