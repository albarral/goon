/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "goon/vision/modules/See.h"

namespace goon
{    
log4cxx::LoggerPtr See::logger(log4cxx::Logger::getLogger("goon.test"));

See::See() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    oRetinalVision = 0;
    oPeripheralVision = 0;
    beat = 0;
}

See::~See()
{
    if (oRetinalVision != 0)
        delete (oRetinalVision);
    
    if (oPeripheralVision != 0)
        delete(oPeripheralVision);    
}
  
void See::init(Capture& oCapture, VisualData& oVisualData, GoonBus& oLookBus)
{
    pGoonBus = &oLookBus;
    pCapture = &oCapture;
    pVisualData = &oVisualData;  
    oRetinalVision = new RetinalVision(oVisualData.getRetina());
    oPeripheralVision = new PeripheralVision(oVisualData.getRetina(), oVisualData.getROIs());
    
    binitialized = true;  
    LOG4CXX_INFO(logger, "See initialized");             
};

void See::first()
{    
    log4cxx::NDC::push("See");   	
    
    // we start in LOST state
    if (binitialized)
    {
        LOG4CXX_INFO(logger, "started");  
        setState(See::eSTATE_ON);
        
        // set sizes for retinal vision
        wait4FirstCapture();
        pCapture->getImageCopy(imageCam);
        LOG4CXX_INFO(logger, "IMAGE SIZE " << imageCam.cols << "x" << imageCam.rows);    
        oRetinalVision->init(imageCam.cols, imageCam.rows); // w, h
        oClick.start();
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized Going off ... ");  
        Module3::off();        
    }
}

void See::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void See::loop()
{   
    // get copy of last camera image
    pCapture->getImageCopy(imageCam);            
    // processes it 
    LOG4CXX_DEBUG(logger, "retinal ... ");
    oRetinalVision->update(imageCam);    
    oRetinalVision->computeCovariances();         
    LOG4CXX_DEBUG(logger, "peripheral ... ");
    oPeripheralVision->update();    
    
    // stores dynamic visual data into static one 
    LOG4CXX_TRACE(logger, "clone retina ... ");
    pVisualData->storeRetinaPhoto();
    LOG4CXX_TRACE(logger, "clone ROIS ... ");
    pVisualData->storeROIsPhoto();

    // measure processing speed
    oClick.read();    
    oClick.start();
    fps = 1000.0/oClick.getMillis();
    beat++;
    // SO
    pGoonBus->getSO_SEE_BEAT().setValue(beat);
    pGoonBus->getSO_SEE_FPS().setValue(fps);
}

void See::wait4FirstCapture()
{
    LOG4CXX_INFO(logger, "waiting for first image");     
    // wait for new grabbed frame (50ms waits)
    while (pCapture->getFrameNum() == 0)            
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