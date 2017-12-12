/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include <stdexcept>      
#include <string>

#include <opencv2/opencv.hpp>

#include <log4cxx/logger.h>
#include "log4cxx/ndc.h"
#include <log4cxx/xml/domconfigurator.h>

#include "goon/vision/LookManager.h"
#include "goon/vision/modules/LookMonitor.h"

#include "goon/vision/test/TestBodies.h"
#include "goon/vision/test/TestRegions.h"



static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("goon.test"));


int launchVision();
int testVision();
int oneShotTest();
void oneShotTest2(); 
int test2();

int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    log4cxx::NDC::push("main");    

    try
    {
        launchVision();
        //testVision(); 
        //oneShotTest();
        //test2();
    }
    catch (const std::exception& ex)
    {
      LOG4CXX_ERROR(logger, "main: Error testing vision - " << ex.what());
      return -1;
    }
    catch (...) // catch-all handler
    {
        LOG4CXX_ERROR(logger, "main: Error testing vision ");
        return -1;
    }

    return 0;
}

int launchVision() 
{        
    LOG4CXX_INFO(logger, "\n\nLAUNCH goon VISION ...\n");

    goon::LookManager oLookManager;
    oLookManager.startModules();
        
    sleep(10);
    
    oLookManager.stopModules();
}    

void oneShotTest2() 
{        
    LOG4CXX_INFO(logger, "\n\nONE SHOT TEST goon VISION ...\n");

    int workingCamera = goon::Grab::eIMAGE_CAMPUS_HALL1;
       
    goon::LookManager oLookManager;
    oLookManager.oneShot(workingCamera);
        
    // VISION MONITORING
    goon::LookMonitor oLookMonitor;
    oLookMonitor.oneShot();

    LOG4CXX_INFO(logger, "END of test ...");
}

/*
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
    oSee.on();    
    
    sleep(1);    
    if (oGrab.isOff() || oSee.isOff())
    {      
        LOG4CXX_ERROR(logger, "Test failed!");
        return -1;
    }
    
    // VISION MONITORING
    cv::Mat imageCam;
    cv::Mat imageRetina;
    cv::Mat imageROIs;
    goon::RetinaMonitor oRetinaMonitor;
    goon::ROIsMonitor oROIsMonitor;
    goon::DualWindow oDualWindow; 
    //oDualWindow.reSize(320, 240);     // makes it crash
    cv::namedWindow("Vision");         
           
    // done here to avoid problems (due to undefined imageRetina on first show)
    oCapture.getImageCopy(imageCam);
    oRetinaMonitor.drawRegions(imageCam, oSee.getRetina2().getListRegions());               
    oROIsMonitor.drawRois(imageCam, oSee.getROIs2().getList());                

    imageRetina = oRetinaMonitor.getOutput();                
    imageROIs = oROIsMonitor.getOutput();                 

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
        }

        cv::waitKey(10);         
        i++;        
    }
 
    // stop modules
    oSee.off();
    oSee.wait();
    
    oGrab.off();
    oGrab.wait();
    
    LOG4CXX_INFO(logger, "END of test ...");
    return 0;
}
*/

/*
// Executes a single iteration of the See module
int oneShotTest() 
{        
    LOG4CXX_INFO(logger, "\n\nONE SHOT TEST goon VISION ...\n");

    int workingCamera = goon::Grab::eIMAGE_CAMPUS_HALL1;
       
    oLook
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
    sleep(1);
    if (oGrab.isOff())
    {      
        LOG4CXX_ERROR(logger, "Test failed!");
        return -1;
    }
    
    oSee.oneShot();
    
    // VISION MONITORING
    cv::Mat imageCam;
    cv::Mat imageRetina;
    cv::Mat imageROIs;
    goon::RetinaMonitor oRetinaMonitor;
    goon::ROIsMonitor oROIsMonitor;
    goon::DualWindow oDualWindow; 
    goon::RetinaSaver oRetinaSaver;
    oRetinaSaver.setDestinationFolder("/home/albarral/TESTS/VISION");
           
    oCapture.getImageCopy(imageCam);
    oRetinaMonitor.drawRegions(imageCam, oSee.getRetina2().getListRegions());               
    oROIsMonitor.drawRois(imageCam, oSee.getROIs2().getList());                
    oRetinaSaver.saveRegions(imageCam, oSee.getRetina2().getListRegions());

    imageROIs = oROIsMonitor.getOutput();                 
    oDualWindow.setImageLeft(imageROIs);
    imageRetina = oRetinaMonitor.getOutput();                
    oDualWindow.setImageRight(imageRetina);

    cv::namedWindow("Vision");         
    cv::imshow("Vision", oDualWindow.getImage());           
    cv::waitKey(0); // wait for keyb interaction
        
    oGrab.off();
    oGrab.wait();
    
    LOG4CXX_INFO(logger, "END of test ...");
    return 0;
}
 */

int test2()
{
    goon::TestBodies oTestBodies;
    oTestBodies.test();
    
    //goon::TestRegions oTestRegions;
    //oTestRegions.testMerge();
    return 0;
}