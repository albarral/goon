/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"
//#include <opencv2/opencv.hpp> // for imshow

#include "goon/main/test/TestObjects.h"
#include "goon/features/structure/Structure2.h"

using namespace log4cxx;

namespace goon
{    
LoggerPtr TestObjects::logger(Logger::getLogger("goon.main"));

void TestObjects::test() 
{        
    LOG4CXX_INFO(logger, "TEST OBJECTS ..."); 
    
    // simulate an object detection with 3 sub-bodies and its recognition
    // the visual memory is initially empty, so 2 iterations are needed (first for object memorization, second for recognition)
    CortexVision oCortexVision;
    Object oObject;                        
    std::vector<Body> listBodies;
    
    for (int i=0; i<2; i++)
    {
        LOG4CXX_INFO(logger, "i = " << std::to_string(i)); 
     
        // create 3 sub-bodies
        createBodies(listBodies);
        // create an object with the sub-bodies
        createObject(oObject, listBodies);
        
        // recognize object
        identifyObject(oCortexVision, oObject);
    }
    
    listBodies.clear();    
}

// this method creates 3 rectangular bodies (lying in horizontal distribution)
// and puts them in the given list
void TestObjects::createBodies(std::vector<Body>& listBodies)
{                
    listBodies.clear();
    
    // bodies size
    int w = 20;
    int h = 10;

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
    mask(window1).setTo(255);
    // second region
    mask(window2).setTo(255);
    // third region
    mask(window3).setTo(255);
    
    // create 3 bodies
    Body oBody1, oBody2, oBody3;    
    oBody1.setMaskAndWindow(mask, window1);
    oBody2.setMaskAndWindow(mask, window2);
    oBody3.setMaskAndWindow(mask, window3);   

    // add them to the list
    listBodies.push_back(oBody1);
    listBodies.push_back(oBody2);
    listBodies.push_back(oBody3);    
            
    // compute their masses & shapes (as done in the goon segmentation)
    for (Body& oBody : listBodies)
    {
        oBody.computeMass();
        oBody.computeBlob();    
    }
}

// this method creates an object with the given list of bodies
// and computes its structure
void TestObjects::createObject(Object& oObject, std::vector<Body>& listBodies)
{              
    // clear the object
    oObject.clear();

    // build the object with the sub-bodies
    int counter = 0;
    for (Body& oBody : listBodies)
    {
        // form object (assign first body & merge the rest)
        if (counter == 0)
            oObject.setBody(oBody);            
        else
            oObject.merge(oBody);            

        // add subbodies
        oObject.addSubBody(oBody);        
        counter++;
    }

    LOG4CXX_INFO(logger, oObject.toString()); 
    LOG4CXX_INFO(logger, oObject.getStructure().toString()); 

//    cv::namedWindow("object");             
//    cv::imshow("object", oObject.getMask());           
//    cv::waitKey(0); // wait for keyb interaction
}

void TestObjects::identifyObject(CortexVision& oCortexVision, Object& oObject)
{
    // model object
    oCortexVision.modelObject(oObject);
    
    // identify 
    if (oCortexVision.identifyObject(oObject))
    {
        LOG4CXX_INFO(logger, "object recognized"); 
    }
    else
    {
        LOG4CXX_INFO(logger, "object not recognized, add to visual memory"); 
        // memorize object if identification fails    
        oCortexVision.memorizeObject();
    }
}
}