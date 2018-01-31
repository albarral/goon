/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"
//#include <opencv2/opencv.hpp> // for imshow

#include "goon/main/test/TestObjects.h"
#include "goon/data/cortex/Object.h"
#include "goon/features/Body.h"

using namespace log4cxx;

namespace goon
{    
LoggerPtr TestObjects::logger(Logger::getLogger("goon.main"));

void TestObjects::test() 
{        
    LOG4CXX_INFO(logger, "TEST OBJECTS ..."); 
    
    // objects size
    int w = 20;
    int h = 10;
    int mass = w+h;

    // 3 positions
    int x1 = 10, x2 = 50, x3 = 90;
    int y = 50;
    
    // 3 windows
    cv::Rect window1 = cv::Rect (x1, y, w, h);
    cv::Rect window2 = cv::Rect (x2, y, w, h);
    cv::Rect window3 = cv::Rect (x3, y, w, h);

    // 1 mask with 3 rectangular regions
    cv::Mat mask = cv::Mat::zeros(100, 200, CV_8U);
    // first region
    cv::Mat maskAux = mask(window1);
    maskAux.setTo(cv::Scalar(255, 255, 255));
    // second region
    maskAux = mask(window2);
    maskAux.setTo(cv::Scalar(255, 255, 255));
    // third region
    maskAux = mask(window3);
    maskAux.setTo(cv::Scalar(255, 255, 255));
    
    // 3 bodies
    Body oBody1, oBody2, oBody3;    
    oBody1.setMaskAndWindow(mask, window1);
    oBody2.setMaskAndWindow(mask, window2);
    oBody3.setMaskAndWindow(mask, window3);
    // compute them
    oBody1.setMass(mass);
    oBody1.computeBasicShape();
    oBody2.setMass(mass);
    oBody2.computeBasicShape();
    oBody3.setMass(mass);
    oBody3.computeBasicShape();
    
    // form object
    Object oObject;                    
    // object = body1
    oObject.setBody(oBody1);
    oObject.addSubBody(oBody1);
    // object += body2
    oObject.merge(oBody2);
    oObject.addSubBody(oBody2);
    // object += body3
    oObject.merge(oBody3);
    oObject.addSubBody(oBody3);

    // compute object's shape
    oObject.computeBasicShape();
    oObject.computeComplexShape();            

    // compute object structure ...    
    // set object center as reference
    cv::Point centroid(oObject.getPos()[0], oObject.getPos()[1]);
    oObject.getStructure().setReference(centroid, oObject.getCovariances(), oObject.getMass());
    
    // get list of elements for the structure
    std::vector<cv::Vec3i> listElements;
    for (Body& oBody : oObject.getSubBodies())
    {
        cv::Vec2i& pos = oBody.getPos();
        cv::Vec3i element(pos[0], pos[1], oBody.getMass());
        listElements.push_back(element);
    }    
    
    // and compute it
    oObject.getStructure().computeStructure(listElements);

    LOG4CXX_INFO(logger, oObject.toString()); 
    LOG4CXX_INFO(logger, oObject.getStructure().getMatStructure()); 

//    cv::namedWindow("object");             
//    cv::imshow("object", oObject.getMask());           
//    cv::waitKey(0); // wait for keyb interaction
 //    */    
}

}