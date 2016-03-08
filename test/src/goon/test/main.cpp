/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <log4cxx/logger.h>
#include "log4cxx/ndc.h"
#include <log4cxx/xml/domconfigurator.h>

#include "goon/data/capture.h"
#include "goon/data/visual_data.h"
#include "goon/test/modules/Grab.h"
#include "goon/test/modules/See.h"

#include "goon/monitor/RetinaMonitor.h"
#include "goon/monitor/ROIsMonitor.h"
#include "goon/monitor/RetinaSaver.h"
#include "goon/show/DualWindow.h"
//#include "goon/show/ImageSave.h"

//#define ONE_SHOT_TEST

static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("goon.test"));

int testVision();

int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    log4cxx::NDC::push("main");    

    testVision(); 
   
    return 0;
}

// test VISION MANAGER
int testVision() 
{        
    LOG4CXX_INFO(logger, "\n\nTESTING goon VISION ...\n");
    bool bmonitor = true;       // monitor vision

    int workingCamera = goon::Grab::eCAM_WEBCAM;        
//    int workingCamera = goon::Grab::eCAM_IPCAM;
//    int workingCamera = goon::Grab::eVIDEO_CAMPUS_HALL;
//    int workingCamera = goon::Grab::eIMAGE_CAMPUS_HALL1;
       
    // shared data for VISION modules
    goon::VisualData oVisualData;    
    goon::Capture oCapture;
    
    // grab module (grabs images from camera)
    goon::Grab oGrab;
    oGrab.init(oCapture, workingCamera);
    oGrab.setFrequency(30.0);
    // see module (retinal & peripheral vision)
    goon::See oSee;
    oSee.init(oCapture, oVisualData);
    oSee.setFrequency(20.0);    // to just wait 50ms among loops
    // launch modules
    oGrab.on();
#ifndef ONE_SHOT_TEST
    oSee.on();
#endif
    
    sleep(1);
#ifndef ONE_SHOT_TEST
    if (oGrab.isOff() || oSee.isOff())
#else
        if (oGrab.isOff())
#endif            
    {      
        LOG4CXX_ERROR(logger, "Test failed!");
        return -1;
    }
    
#ifdef ONE_SHOT_TEST
    oSee.oneShot();
#endif    
    
    // VISION MONITORING
    cv::Mat imageCam;
    cv::Mat imageRetina;
    cv::Mat imageROIs;
    goon::RetinaMonitor oRetinaMonitor;
    goon::ROIsMonitor oROIsMonitor;
    goon::DualWindow oDualWindow; 
    goon::RetinaSaver oRetinaSaver;
    oRetinaSaver.setDestinationFolder("/home/albarral/TESTS/VISION");
    //oDualWindow.reSize(320, 240);     // makes it crash
    cv::namedWindow("Vision");         
           
    //goon::ImageSave oImageSave;
    //oImageSave.setPath("/home/albarral/TESTS/VISION");
    //oImageSave.setVideo(true);    

    // done here to avoid problems (due to undefined imageRetina on first show)
    oCapture.getImageCopy(imageCam);
    oRetinaMonitor.drawRegions(imageCam, oSee.getRetina2().getListRegions());               
    imageRetina = oRetinaMonitor.getOutput();                
    oROIsMonitor.drawRois(imageCam, oSee.getROIs2().getList());                
    imageROIs = oROIsMonitor.getOutput();                 
#ifdef ONE_SHOT_TEST
    oRetinaSaver.saveRegions(imageCam, oSee.getRetina2().getListRegions());
#endif    

    int i=1;
    int frameNum = oCapture.getFrameNum();
    int counter = oSee.getCounter();
    while (i<200)
    {        
        //LOG4CXX_DEBUG(logger, "iteration " << i);        
        
        // wait for new grabbed frame
        while (oCapture.getFrameNum() == frameNum)            
            usleep(50000);
        
        frameNum = oCapture.getFrameNum();
        oCapture.getImageCopy(imageCam);
        
        // show processed image
        if (bmonitor)
        {            
            // after each See loop the monitor shows the new updated retina 
            if (oSee.getCounter() > counter)
            {
                counter = oSee.getCounter();       
                // draw regions obtained by the retinal vision system (from a copy of the retina)
                oRetinaMonitor.drawRegions(imageCam, oSee.getRetina2().getListRegions());            
                imageRetina = oRetinaMonitor.getOutput();
                // draw ROIs obtained by the peripheral vision system (from a copy of the ROIs) )
                oROIsMonitor.drawRois(imageCam, oSee.getROIs2().getList());                
                oROIsMonitor.drawFPS(oSee.getFps());
                imageROIs = oROIsMonitor.getOutput();                                
            }            

            //oDualWindow.setImageLeft(imageCam);
            oDualWindow.setImageLeft(imageROIs);
            oDualWindow.setImageRight(imageRetina);
            cv::imshow("Vision", oDualWindow.getImage());   
            //oImageSave.save(oDualWindow.getImage());
        }

        cv::waitKey(10);         
        i++;        
    }
 
#ifndef ONE_SHOT_TEST
    // stop modules
    oSee.off();
    oSee.wait();
#endif    
    
    oGrab.off();
    oGrab.wait();
    
    LOG4CXX_INFO(logger, "END of test ...");
    return 0;
}
