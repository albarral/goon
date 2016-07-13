/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream> 
#include <vector>   

#include <opencv2/opencv.hpp>

#include "goon/look/test/TestBodies.h"
#include "goon/data/base/Body.h"
#include "goon/data/base/BodyUtils.h"

namespace goon
{    

void TestBodies::test() 
{        
    std::cout << "TEST BODIES ..." << std::endl;
    
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
        
    // paint rectangles
    cv::Scalar color = cv::Scalar(255, 255, 255);  // white
    cv::rectangle(mask1, window1, color, -1);
    cv::rectangle(mask2, window2, color, -1);
    cv::rectangle(mask3, window3, color, -1);
    cv::rectangle(mask4, window4, color, -1);
    cv::rectangle(mask5, window5, color, -1);
    cv::rectangle(mask6, window6, color, -1);
    
    // create bodies
    Body oBody1, oBody2, oBody3, oBody4, oBody5, oBody6;
    oBody1.setMaskAndWindow(mask1, window);
    oBody2.setMaskAndWindow(mask2, window);
    oBody3.setMaskAndWindow(mask3, window);
    oBody4.setMaskAndWindow(mask4, window);
    oBody5.setMaskAndWindow(mask5, window);
    oBody6.setMaskAndWindow(mask6, window);

    std::vector<Body> listBodies;
    listBodies.push_back(oBody1);
    listBodies.push_back(oBody2);
    //listBodies.push_back(oBody3);
    listBodies.push_back(oBody4);
    listBodies.push_back(oBody5);
    listBodies.push_back(oBody6);

    for (goon::Body& oBody : listBodies)
    {
        oBody.computeMass();        
    }
    oBody3.computeMass(); 

    // get which body best overlaps Body3
    goon::st_bodyOverlap bestOverlap = goon::BodyUtils::getBestOverlap(oBody3, listBodies);

    std::cout << bestOverlap.body2 << " - " << bestOverlap.overlap1 << ", " << bestOverlap.overlap2 << std::endl;
    
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

}