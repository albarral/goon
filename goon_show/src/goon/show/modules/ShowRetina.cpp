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
    binitialized = false;
    pGoonBus = 0;
    pCapture = 0;
    pVisualData = 0;      
    windowName = "Retina";
}

ShowRetina::~ShowRetina() 
{
}

void ShowRetina::init(Capture& oCapture, VisualData& oVisualData, GoonBus& oGoonBus)
{
    pGoonBus = &oGoonBus;
    pCapture = &oCapture;
    pVisualData = &oVisualData;      
    binitialized = true;  
    LOG4CXX_INFO(logger, "ShowRetina initialized");             
};

void ShowRetina::first()
{ 
    log4cxx::NDC::push("ShowRetina");   	
    LOG4CXX_INFO(logger, "started");  

    //oDualWindow.reSize(320, 240);     // makes it crash
    cv::namedWindow(windowName);         

    // avoid undefined imageRetina on first show
    pCapture->getImageCopy(imageCam);
    imageRetina = imageCam.clone();
    imageROIs = imageCam.clone();

    frameNum = pCapture->getFrameNum();
    // SO_SEE_BEAT
    seeBeat = pGoonBus->getSO_SEE_BEAT().getValue();
}

void ShowRetina::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void ShowRetina::loop()
{
    //LOG4CXX_DEBUG(logger, "iteration " << i);                
    // skip if no new grabbed frame
    if (pCapture->getFrameNum() == frameNum)            
        return;

    frameNum = pCapture->getFrameNum();
    pCapture->getImageCopy(imageCam);
    // SO_SEE_BEAT
    int newBeat = pGoonBus->getSO_SEE_BEAT().getValue();
    float fps = pGoonBus->getSO_SEE_FPS().getValue();

    // on each See beat update the output shown
    if (newBeat != seeBeat)
    {
        seeBeat = newBeat;       
        // draw regions obtained by the retinal vision 
        oRetinaMonitor.drawRegions(imageCam, pVisualData->getRetina2().getListRegions());            
        imageRetina = oRetinaMonitor.getOutput();
        // draw ROIs obtained by the peripheral vision 
        oROIsMonitor.drawRois(imageCam, pVisualData->getROIs2().getList());                
        oROIsMonitor.drawFPS(fps);
        imageROIs = oROIsMonitor.getOutput();                                
    }            

    // show dual window
    oDualWindow.setImageLeft(imageROIs);
    oDualWindow.setImageRight(imageRetina);
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
           
    oRetinaSaver.saveRegions(imageCam,  pVisualData->getRetina2().getListRegions());
}

}
