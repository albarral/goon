/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/look/modules/LookMonitor.h"
#include "goon/monitor/RetinaSaver.h"

namespace goon
{  
log4cxx::LoggerPtr LookMonitor::logger(log4cxx::Logger::getLogger("goon.look"));

LookMonitor::LookMonitor() 
{
    binitialized = false;
    pCapture = 0;
    pVisualData = 0;      
}

LookMonitor::~LookMonitor() 
{
}

void LookMonitor::init(Capture& oCapture, VisualData& oVisualData, LookBus& oLookBus)
{
    pLookBus = &oLookBus;
    pCapture = &oCapture;
    pVisualData = &oVisualData;      
    binitialized = true;  
    LOG4CXX_INFO(logger, "LookMonitor initialized");             
};

void LookMonitor::first()
{ 
    LOG4CXX_INFO(logger, "LookMonitor: first ..."); 
    //oDualWindow.reSize(320, 240);     // makes it crash
    cv::namedWindow("Vision");         

    // avoid undefined imageRetina on first show
    pCapture->getImageCopy(imageCam);
    imageRetina = imageCam.clone();
    imageROIs = imageCam.clone();

    frameNum = pCapture->getFrameNum();
    // SO_SEE_BEAT
    seeBeat = pLookBus->getSO_SEE_BEAT().getValue();
}

void LookMonitor::bye()
{
    LOG4CXX_INFO(logger, "LookMonitor: stop ..."); 

}

void LookMonitor::loop()
{
    //LOG4CXX_DEBUG(logger, "iteration " << i);                
    // skip if no new grabbed frame
    if (pCapture->getFrameNum() == frameNum)            
        return;

    frameNum = pCapture->getFrameNum();
    pCapture->getImageCopy(imageCam);
    // SO_SEE_BEAT
    int newBeat = pLookBus->getSO_SEE_BEAT().getValue();
    float fps = pLookBus->getSO_SEE_FPS().getValue();

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
    cv::imshow("Vision", oDualWindow.getImage());   

    cv::waitKey(10);            
}

// just one loop exectution (for testing)
void LookMonitor::oneShot()
{
    LOG4CXX_INFO(logger, "See - one shot");     
    first();
    loop();    
    
    RetinaSaver oRetinaSaver;
    oRetinaSaver.setDestinationFolder("/home/albarral/TESTS/VISION");
           
    oRetinaSaver.saveRegions(imageCam,  pVisualData->getRetina2().getListRegions());
}

}