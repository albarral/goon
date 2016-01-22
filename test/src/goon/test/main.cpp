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
#include "goon/camera/camera.h"
#include "goon/data/visual_data.h"
#include "goon/retinal/retinal_vision.h"
#include "goon/peripheral/peripheral_vision.h"

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
    LOG4CXX_INFO(logger, "TESTING goon VISION ...");
    bool bmonitor = true;       // monitor vision

    int workingCamera = goon::CameraFactory::eCAM_WEBCAM;        
//    int workingCamera = goon::CameraFactory::eCAM_IPCAM;
//    int workingCamera = goon::CameraFactory::eVIDEO_CAMPUS_HALL;
//    int workingCamera = goon::CameraFactory::eIMAGE_CAMPUS_HALL1;
    
    goon::Camera* camera = goon::CameraFactory::createCamera(workingCamera);    
    if (camera->connect() != 0)
    {
        LOG4CXX_ERROR(logger, "FAILED test ...");    
        return -1;
    }
    
    LOG4CXX_INFO(logger, "camera connected");
    
    goon::DualWindow oDualWindow; 
    //oDualWindow.reSize(320, 240);     // makes it crash
    cv::namedWindow("Vision");         

    //goon::ImageSave oImageSave;
    //oImageSave.setPath("/home/albarral/TESTS/VISION");
    //oImageSave.setVideo(true);    

    // VISION classes    
    goon::VisualData oVisualData;
    goon::RetinalVision* oRetinalVision = new goon::RetinalVision(oVisualData.getRetina());
    goon::PeripheralVision* oPeripheralVision = new goon::PeripheralVision(oVisualData.getRetina(), oVisualData.getROIs());
    
    int img_w = camera->getImgWidth();
    int img_h = camera->getImgHeight();
    LOG4CXX_INFO(logger, "IMAGE SIZE " << img_w << "x" << img_h);    
    oRetinalVision->resize(img_w, img_h);

    cv::Mat imageCam;
//    cv::Mat imageROIs;
//    cv::Mat imageRetina;
    int i= 0;
    while (i < 50)
    {        
        //LOG4CXX_DEBUG(logger, "iteration " << i);        
        
        // grab image & pass it to the vision system
        camera->grab();        
        camera->getCaptureCopy(&imageCam);
        //oVisionManager.newFrame(image);

        LOG4CXX_DEBUG(logger, "retinal ... ");
        oRetinalVision->update(imageCam);    
        oRetinalVision->computeCovariances();         
        LOG4CXX_DEBUG(logger, "peripheral ... ");
        oPeripheralVision->update();    
        
        // show processed image
        if (bmonitor)
        {
//            oVisionManager.monitorROIs(image);
//            oVisionManager.monitorRetina(image);
//            imageROIs = oVisionManager.getPhotoROIs();
//            imageRetina = oVisionManager.getPhotoRetina();

            oDualWindow.setImageLeft(imageCam);
//            oDualWindow.setImageLeft(imageROIs);
//            oDualWindow.setImageRight(imageRetina);
            cv::imshow("Vision", oDualWindow.getImage());   
            //oImageSave.save(oDualWindow.getImage());
        }

        cv::waitKey(10);         
        i++;        
    }
 
    
    if (oRetinalVision != NULL)
        delete (oRetinalVision);
    if (oPeripheralVision != NULL)
        delete (oPeripheralVision);

    LOG4CXX_INFO(logger, "END of test ...");
    return 0;
}
