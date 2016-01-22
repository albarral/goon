/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/imgproc/imgproc.hpp>          // for cv::resize

#include "goon/show/DualWindow.h"

namespace goon 
{
// Constructor
DualWindow::DualWindow ()
{    
    size.width = size.height = 0;
    // default size is VGA
    reSize(640, 480);    
}

void DualWindow::reSize(int singleW, int singleH)
{
    if (singleW <= 0 || singleH <= 0)
        return;
    
    if (size.width != singleW || size.height != singleH)
    {
        size.width = singleW;
        size.height = singleH;
        image.create(size.height, 2*size.width, CV_8UC3);    
        cv::Rect windowL = cv::Rect(0, 0, size.width, size.height);
        cv::Rect windowR = cv::Rect(size.width, 0, size.width, size.height);
        imageL = image(windowL);
        imageR = image(windowR);
    }    
}

void DualWindow::setImageLeft(cv::Mat& image)
{     
    if (image.cols > size.width)
        image = scaleDown(image);
    
    image.copyTo(imageL);
}

void DualWindow::setImageRight(cv::Mat& image)
{      
    if (image.cols > size.width)
        image = scaleDown(image);

    image.copyTo(imageR);
}

cv::Mat DualWindow::scaleDown(cv::Mat& image)
{
    cv::Mat imageScaled;    
    cv::resize(image, imageScaled, size, 0, 0, cv::INTER_AREA);
    
    return imageScaled;
}
}