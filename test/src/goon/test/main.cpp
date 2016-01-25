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

#include "goon/test/camera_factory.h"
#include "goon/data/visual_data.h"
#include "goon/test/modules/Grabber.h"
#include "goon/test/modules/See.h"

#include "goon/monitor/RetinaMonitor.h"
#include "goon/monitor/ROIsMonitor.h"
#include "goon/show/DualWindow.h"
//#include "goon/show/ImageSave.h"


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

    int workingCamera = goon::CameraFactory::eCAM_WEBCAM;        
//    int workingCamera = goon::CameraFactory::eCAM_IPCAM;
//    int workingCamera = goon::CameraFactory::eVIDEO_CAMPUS_HALL;
//    int workingCamera = goon::CameraFactory::eIMAGE_CAMPUS_HALL1;
       
    // VISION modules
    goon::VisualData oVisualData;    
    // grabber module (grabs image from camera & passes them to the vision system)
    goon::Grabber oGrabber;
    oGrabber.init(oVisualData, workingCamera);
    oGrabber.setFrequency(30.0);
    // see module (performs retinal & peripheral vision)
    goon::See oSee;
    oSee.init(oVisualData);
    oSee.setFrequency(20.0);

    // launch modules
    oGrabber.on();
    oSee.on();
    sleep(1);
    if (oGrabber.isOff() || oSee.isOff())
    {      
        LOG4CXX_ERROR(logger, "Test failed!");
        return -1;
    }

    // VISION MONITORING
    goon::RetinaMonitor oRetinaMonitor;
    goon::ROIsMonitor oROIsMonitor;
    goon::DualWindow oDualWindow; 
    //oDualWindow.reSize(320, 240);     // makes it crash
    cv::namedWindow("Vision");         

    //goon::ImageSave oImageSave;
    //oImageSave.setPath("/home/albarral/TESTS/VISION");
    //oImageSave.setVideo(true);    
            
    cv::Mat imageCam;
    cv::Mat imageRetina;
    cv::Mat imageROIs;
    int i= 0;
    int frameNum = oVisualData.getFrameNum();
    while (i < 200)
    {        
        //LOG4CXX_DEBUG(logger, "iteration " << i);        
        
        // wait for new grabbed frame
        while (oVisualData.getFrameNum() == frameNum)            
            usleep(50000);
        
        frameNum = oVisualData.getFrameNum();
        oVisualData.getCopyImageCam(imageCam);
        
        // show processed image
        if (bmonitor)
        {
            // IMPORTANT: A copy of the regions & rois SHOULD be used in order to avoid parallel thread undesired effects!!!
            oRetinaMonitor.drawRegions(imageCam, oVisualData.getRetina().getListRegions());
            oROIsMonitor.draw(imageCam, oVisualData.getROIs().getList());
            imageRetina = oRetinaMonitor.getOutput();
            imageROIs = oROIsMonitor.getOutput();

            oDualWindow.setImageLeft(imageCam);
            oDualWindow.setImageRight(imageROIs);
//            oDualWindow.setImageRight(imageRetina);
            cv::imshow("Vision", oDualWindow.getImage());   
            //oImageSave.save(oDualWindow.getImage());
        }

        cv::waitKey(10);         
        i++;        
    }
 
    // stop modules
    oSee.off();
    oSee.wait();
    
    oGrabber.off();
    oGrabber.wait();
    
    LOG4CXX_INFO(logger, "END of test ...");
    return 0;
}
