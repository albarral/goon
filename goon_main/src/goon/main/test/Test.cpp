/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream> 
#include <opencv2/opencv.hpp>

#include "goon/main/test/Test.h"

namespace goon
{    

void Test::testMaskAcces()
{        
    std::cout << "Test mask access ..." << std::endl;

    int w = 640;
    int h = 480;

    cv::Mat mask = cv::Mat::zeros(h, w, CV_8UC1); 
    
    cv::Point point(w, h);  // BAD LOCATION
    int value = mask.at<uchar>(point.y, point.x);
    
    std::cout << "value = " << std::to_string(value) << std::endl;
}

}