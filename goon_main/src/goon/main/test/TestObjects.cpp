/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"
#include <opencv2/opencv.hpp> // for imshow

#include "goon/main/test/TestObjects.h"
#include "goon/data/cortex/Object.h"
#include "goon/features/Blob.h"
#include "goon/features/Body.h"
#include "goon/features/structure/Structure2.h"

using namespace log4cxx;

namespace goon
{    
LoggerPtr TestObjects::logger(Logger::getLogger("goon.main"));

void TestObjects::test() 
{        
    LOG4CXX_INFO(logger, "TEST OBJECTS ..."); 
    
    // this method creates an object from the union of 3 rectangular bodies (lying in horizontal distribution)
    // the object structure is then computed  
    
    // objects size
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
    
    // 3 bodies
    Body oBody1, oBody2, oBody3;    
    oBody1.setMaskAndWindow(mask, window1);
    oBody2.setMaskAndWindow(mask, window2);
    oBody3.setMaskAndWindow(mask, window3);   

    // create bodies list
    std::vector<Body> listBodies;
    listBodies.push_back(oBody1);
    listBodies.push_back(oBody2);
    listBodies.push_back(oBody3);
    
    // create object with the 3 bodies
    Object oObject;                    
    int counter = 0;
    for (Body& oBody : listBodies)
    {
        // compute bodies
        oBody.computeMass();
        oBody.computeBlob();
        // form object
        if (counter == 0)
            oObject.setBody(oBody);            
        else
            oObject.merge(oBody);            
        // add subbodies
        oObject.addSubBody(oBody);        
        counter++;
    }
    
    // compute object's shape
    oObject.computeBlob();
    oObject.computeShape();            

    // compute object structure ...    
    Structure2& oStructure = oObject.getStructure();
    // set object as structure reference
    oStructure.setReferenceBlob(oObject);    
    // get list of elements for the structure
    std::vector<Blob> listBlobs;
    for (Body& oBody : oObject.getSubBodies())
    {
        listBlobs.push_back(oBody);
    }        
    // compute structure
    oStructure.computeStructure(listBlobs);

    LOG4CXX_INFO(logger, oObject.toString()); 
    LOG4CXX_INFO(logger, oStructure.toString()); 

    cv::namedWindow("object");             
    cv::imshow("object", oObject.getMask());           
    cv::waitKey(0); // wait for keyb interaction
    
    listBlobs.clear();
    listBodies.clear();
}

}