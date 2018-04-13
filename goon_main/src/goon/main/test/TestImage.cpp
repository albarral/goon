/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/imgproc/imgproc.hpp"          // for cvtColor

#include "goon/main/test/TestImage.h"
#include "goon/camera/Grabber.h"
#include "tron/util/Environment.h"

namespace goon
{        
TestImage::TestImage()
{
    w = h = 0;
}

void TestImage::createImage(int w, int h)
{            
    this->w = w;
    this->h = h;

    // create test image 
    imageCam = cv::Mat::zeros(h, w, CV_8UC3);         
    // fill red rectangle in image
    int wx = w*0.2;
    int ww = w*0.6;
    int wy = h*0.2;
    int wh = h*0.6;
    cv::Rect windowObject = cv::Rect(wx, wy, ww, wh);
    cv::Mat imageROI = imageCam(windowObject);
    imageROI = cv::Scalar(0, 0, 255);
    // convert to HSV space
    cv::cvtColor(imageCam, imageHSV, CV_BGR2HSV);

    // create mask segmented with a small segmented window (to simulate parallel border detection)
    maskSegmented = cv::Mat::zeros(h, w, CV_8UC1); 
    int sx = wx; 
    int sw = 4; 
    int sy = wy; 
    int sh = 4;
    cv::Rect windowSeg = cv::Rect(sx, sy, sw, sh);
    cv::Mat maskROI = maskSegmented(windowSeg);
    maskROI = cv::Scalar(255);
}

bool TestImage::loadImage()
{
    Grabber oGrabber;   // utility class used for frame grabbing from any source    
    oGrabber.connect2Image(tron::Environment::getHomePath() + "/TESTS/images/image_orange3.jpg");
    if (oGrabber.grab())            
    {
        imageCam = oGrabber.getCapture();
        // convert to HSV space
        cv::cvtColor(imageCam, imageHSV, CV_BGR2HSV);
        
        w = imageCam.cols;
        h = imageCam.rows;
        maskSegmented = cv::Mat::zeros(h, w, CV_8UC1); 
        return true;
    }
    else
        return false;
    
}
}