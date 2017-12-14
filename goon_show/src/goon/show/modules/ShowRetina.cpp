/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "goon/show/modules/ShowRetina.h"
#include "goon/show/monitor/RetinaSaver.h"

namespace goon
{  
log4cxx::LoggerPtr ShowRetina::logger(log4cxx::Logger::getLogger("goon.show"));

ShowRetina::ShowRetina() 
{
    modName = "ShowRetina";
    windowName = "Retina";
}

ShowRetina::~ShowRetina() 
{
}

void ShowRetina::showInitialized()
{
    LOG4CXX_INFO(logger, "ShowRetina initialized");             
};

void ShowRetina::first()
{ 
    log4cxx::NDC::push("ShowRetina");   	
    LOG4CXX_INFO(logger, "started");  

    //oDualWindow.reSize(320, 240);     // makes it crash
    cv::namedWindow(windowName);         

    // avoid undefined imageRetina on first show
    pVisualData->getImageCopy(imageCam);
    imageRetina = imageCam.clone();
    imageROIs = imageCam.clone();

    // sense beats
    grabBeat = pGoonBus->getSO_GRAB_BEAT().getValue();
    seeBeat = pGoonBus->getSO_SEE_BEAT().getValue();
}

void ShowRetina::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void ShowRetina::loop()
{
    //LOG4CXX_DEBUG(logger, "iteration " << i);                

    // if no new capture (grab beat not changed), skip
    if (pGoonBus->getSO_GRAB_BEAT().getValue() == grabBeat)
        return;        
    // if new capture, get it
    else
    {
        pVisualData->getImageCopy(imageCam);
        grabBeat = pGoonBus->getSO_GRAB_BEAT().getValue();
    }
    
    // if new See beat update output
    if (pGoonBus->getSO_SEE_BEAT().getValue() != seeBeat)
    {
        seeBeat = pGoonBus->getSO_SEE_BEAT().getValue();       
        // draw regions obtained by the retinal vision 
        oRetinaMonitor.drawRegions(imageCam, pVisualData->getRetina2().getListRegions());            
        imageRetina = oRetinaMonitor.getOutput();
        // draw ROIs obtained by the peripheral vision 
        oROIsMonitor.drawRois(imageCam, pVisualData->getROIs2().getList());                
        oROIsMonitor.drawFPS(pGoonBus->getSO_SEE_FPS().getValue());
        imageROIs = oROIsMonitor.getOutput();                                

        oDualWindow.setImageLeft(imageROIs);
        oDualWindow.setImageRight(imageRetina);
    }            

    // show dual window
    cv::imshow(windowName, oDualWindow.getImage());   
    cv::waitKey(10);            
}

// just one loop exectution (for testing)
void ShowRetina::oneShot()
{
    first();
    loop();    
    bye();
    
    RetinaSaver oRetinaSaver;
    oRetinaSaver.setDestinationFolder("/home/albarral/TESTS/VISION");
           
    oRetinaSaver.saveRegions(imageCam, pVisualData->getRetina2().getListRegions());
}

}
