/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream> // for test2()
#include <unistd.h>
#include <utility>      // for test2()
#include <vector>   // for test2()
#include <string>

#include <opencv2/opencv.hpp>

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

// for test
#include "goon/features/body/Body.h"
#include "goon/features/body/BodyUtils.h"


static log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("goon.test"));

int testVision();
int oneShotTest();
int test2();

int main(int argc, char** argv) 
{
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
    log4cxx::NDC::push("main");    

    //testVision(); 
    //oneShotTest();
    test2();
   
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

// Executes a single iteration of the See module
int oneShotTest() 
{        
    LOG4CXX_INFO(logger, "\n\nONE SHOT TEST goon VISION ...\n");

    int workingCamera = goon::Grab::eIMAGE_CAMPUS_HALL1;
       
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

int test2() 
{        
    LOG4CXX_INFO(logger, "\n\nTEST 2...\n");
    
    // test overlap computation of two masks (200 x 100) half filled

    // masks
    int w = 200;
    int h = 100;
    cv::Mat mask1 = cv::Mat::zeros (h, w, CV_8U);
    cv::Mat mask2 = mask1.clone();
    cv::Mat mask3 = mask1.clone();
    cv::Mat mask4 = mask1.clone();
    cv::Mat mask5 = mask1.clone();
    cv::Mat mask6 = mask1.clone();
    cv::Rect window = cv::Rect (0, 0, w, h);
    
    // windows
    int base = w/4; // 50
    int alt = h/2;     // 50
    cv::Rect window1 = cv::Rect (0, 0, base, alt);
    cv::Rect window2 = cv::Rect (base, 0, base, alt);
    cv::Rect window3 = cv::Rect (2*base, 0, 2*base, alt);
    int disp = alt/4;
    cv::Rect window4 = cv::Rect (0, disp, base, alt);
    cv::Rect window5 = cv::Rect (base, 3*disp, base, alt);
    cv::Rect window6 = cv::Rect (2*base, 2*disp, 2*base, alt);
        
    // pait rectangles
    cv::Scalar color = cv::Scalar(255, 255, 255);  // white
    cv::rectangle(mask1, window1, color, -1);
    cv::rectangle(mask2, window2, color, -1);
    cv::rectangle(mask3, window3, color, -1);
    cv::rectangle(mask4, window4, color, -1);
    cv::rectangle(mask5, window5, color, -1);
    cv::rectangle(mask6, window6, color, -1);
    
    // create bodies
    goon::Body oBody1, oBody2, oBody3, oBody4, oBody5, oBody6;
    oBody1.setMask(mask1, window);
    oBody2.setMask(mask2, window);
    oBody3.setMask(mask3, window);
    oBody4.setMask(mask4, window);
    oBody5.setMask(mask5, window);
    oBody6.setMask(mask6, window);

    std::vector<goon::Body> listBodies;
    listBodies.push_back(oBody1);
    listBodies.push_back(oBody2);
    //listBodies.push_back(oBody3);
    listBodies.push_back(oBody4);
    listBodies.push_back(oBody5);
    listBodies.push_back(oBody6);
           
    goon::st_bodyOverlap bestOverlap = goon::BodyUtils::getBestOverlap(oBody3, listBodies);

    std::cout << bestOverlap.body2 << " - " << bestOverlap.mutualOverlap << std::endl;
    
//    /*
    cv::namedWindow("mask1");         
    cv::namedWindow("mask2");         
    cv::namedWindow("mask3");         
    cv::namedWindow("mask4");         
    cv::namedWindow("mask5");         
    cv::namedWindow("mask6");         
    cv::imshow("mask1", mask1);           
    cv::imshow("mask2", mask2);           
    cv::imshow("mask3", mask3);           
    cv::imshow("mask4", mask4);           
    cv::imshow("mask5", mask5);           
    cv::imshow("mask6", mask6);           
    cv::waitKey(0); // wait for keyb interaction
 //    */
    
}