/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "goon/test/modules/See.h"

namespace goon
{    
log4cxx::LoggerPtr See::logger(log4cxx::Logger::getLogger("goon.test"));

See::See() 
{
    //  initial state must be Module2::state_OFF
    binitialized = false;
    oRetinalVision = 0;
    oPeripheralVision = 0;
    counter = 0;
}

See::~See()
{
    if (oRetinalVision != 0)
        delete (oRetinalVision);
    
    if (oPeripheralVision != 0)
        delete(oPeripheralVision);    
}
  
void See::init(VisualData& oVisualData)
{
    // get shared visual data
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
        setPrevState(Module::state_OFF);
        
        // set sizes for retinal vision
        wait4ValidImage();
        pVisualData->getCopyImageCam(imageCam);
        LOG4CXX_INFO(logger, "IMAGE SIZE " << imageCam.cols << "x" << imageCam.rows);    
        oRetinalVision->init(imageCam.cols, imageCam.rows); // w, h
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized Going off ... ");  
        Module::off();        
    }
}

void See::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void See::loop()
{   
    // get copy of last camera image
    pVisualData->getCopyImageCam(imageCam);
    // processes it 
    LOG4CXX_DEBUG(logger, "retinal ... ");
    oRetinalVision->update(imageCam);    
    oRetinalVision->computeCovariances();         
    LOG4CXX_DEBUG(logger, "peripheral ... ");
    oPeripheralVision->update();    
    
    // stores retina info for debugging purpose
    std::lock_guard<std::mutex> locker(mutex);
    LOG4CXX_TRACE(logger, "clone retina ... ");
    oRetina2 = pVisualData->getRetina();
    counter++;
}

void See::wait4ValidImage()
{
    LOG4CXX_INFO(logger, "waiting for first image");     
    // wait for new grabbed frame (50ms waits)
    while (pVisualData->getFrameNum() == 0)            
        usleep(50000);
}

int See::getCounter()
{
    std::lock_guard<std::mutex> locker(mutex);
    return counter;   
}

Retina& See::getRetina2()
{
    std::lock_guard<std::mutex> locker(mutex);
    return oRetina2;    
}  

}