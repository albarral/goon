/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/test/camera_factory.h"
#include "goon/camera/models/web_camera.h"
#include "goon/camera/models/ip_camera.h"
#include "goon/camera/models/video_flow.h"
#include "goon/camera/models/image_flow.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr CameraFactory::logger(Logger::getLogger("goon.camera"));

Camera* CameraFactory::createCamera(int option)
{
    Camera* oCamera;
        
    switch (option)
    {
        case CameraFactory::eCAM_WEBCAM:                        
            oCamera = new WebCamera(0);
            oCamera->setVisualField(33);                
            LOG4CXX_INFO(logger, "Web camera");
            break;

        case CameraFactory::eCAM_IPCAM:                        
            oCamera = new ipCamera("http://192.168.1.3/video.cgi?.mjpg");
            oCamera->setVisualField(33);                
            oCamera->setCamHeight(25);
            LOG4CXX_INFO(logger, "IP camera");
            break;
            
        case CameraFactory::eCAM_WIFIBOT_WIRELESS:            
            oCamera = new ipCamera("http://192.168.1.105/video.cgi?.mjpg");
            oCamera->setVisualField(33);                
            oCamera->setCamHeight(25);
            LOG4CXX_INFO(logger, "IP camera: Wifibot (wireless)");
            break;

        case CameraFactory::eCAM_ALBARRACIN:
            oCamera = new ipCamera("http://212.170.22.153:8080/mjpg/video.mjpg");
            LOG4CXX_INFO(logger, "IP camera: webcam Albarracin");
            break;

        case CameraFactory::eCAM_SOUTHERN_BEACH:
            oCamera = new ipCamera("http://66.184.211.231/mjpg/video.mjpg");
            LOG4CXX_INFO(logger, "IP camera: webcam Southernmost beach");
            break;
            
        case eVIDEO_CAMPUS_HALL:
            oCamera = new VideoFlow("/home/albarral/PROJECTS/IMAGES/sequences/campus_hall.MP4");
            LOG4CXX_INFO(logger, "Video: campus hall");
            break;
            
        case eIMAGE_CAMPUS_HALL1:
            oCamera = new ImageFlow("/home/albarral/TESTS/images/campus_hall1.png");
            LOG4CXX_INFO(logger, "Image: campus hall 1");
            break;
            
        case eIMAGE_CAMPUS_HALL2:
            oCamera = new ImageFlow("/home/albarral/TESTS/images/campus_hall2.png");
            LOG4CXX_INFO(logger, "Image: campus hall 2");
            break;

        case eIMAGE_CAMPUS_HALL3:
            oCamera = new ImageFlow("/home/albarral/TESTS/images/campus_hall3.png");
            LOG4CXX_INFO(logger, "Image: campus hall 3");
            break;

        case eIMAGE_CAMPUS_HALL4:
            oCamera = new ImageFlow("/home/albarral/TESTS/images/campus_hall4.png");
            LOG4CXX_INFO(logger, "Image: campus hall 4");
            break;

        case eIMAGE_BABOON:
            oCamera = new ImageFlow("/home/albarral/TESTS/images/baboon.jpg");
            LOG4CXX_INFO(logger, "Image: babbon");
            break;

        case eIMAGE_FRUITS:
            oCamera = new ImageFlow("/home/albarral/TESTS/images/fruits.jpg");
            LOG4CXX_INFO(logger, "Image: fruits");
            break;

        case eIMAGE_JLUIS:
            oCamera = new ImageFlow("/home/albarral/TESTS/images/jluis.jpg");
            LOG4CXX_INFO(logger, "Image: jluis");
            break;
            
        default:
            oCamera = NULL;
    }

    return oCamera;
}
}

