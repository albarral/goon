/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include <string>

#include "goon/monitor/Draw.h"

//using namespace cv;

namespace goon
{
// Constructor
Draw::Draw ()
{    
    color = cv::Scalar(255, 255, 255);  // white
    bsized = false;
}


void Draw::setSize(cv::Mat& image)
{      
    image_draw.create(image.rows, image.cols, image.type());
    bsized = true;    
}


void Draw::setBackGround(cv::Mat& image)
{      
    if (!bsized)        
        setSize(image);

    image.copyTo(image_draw);
}


void Draw::clearBackGround()
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }
        
    image_draw.setTo(cv::Scalar(0));
}


void Draw::setExactColor(cv::Vec3f& rgb_color)
{
    color = cv::Scalar(rgb_color[2], rgb_color[1], rgb_color[0]);      // BGR
}


void Draw::drawMask(cv::Mat& mask)
{                
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    image_draw.setTo(color, mask);
}


void Draw::drawMask(cv::Mat& mask, cv::Rect& window)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    cv::Mat image_roi = image_draw(window);
    image_roi.setTo(color, mask);
}


void Draw::drawPoint(cv::Point& point, int def_color, int radius)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    setDefaultColor(def_color);    
    cv::circle(image_draw, point, radius, color, -1);
}


void Draw::drawEllipse(cv::Point& center, int width, int height, int orientation)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }
    
    setDefaultColor(Draw::eYELLOW);       
    cv::ellipse (image_draw, center, cv::Size(width, height), orientation, 0, 360, color, 3);
}


void Draw::drawHLine(int row)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    cv::Point pt1(0, row);
    cv::Point pt2(image_draw.cols-1, row);
    cv::line(image_draw, pt1, pt2, color);    
}

        
void Draw::drawVLine(int col)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    cv::Point pt1(col, 0);
    cv::Point pt2(col, image_draw.rows-1);
    cv::line(image_draw, pt1, pt2, color);    
}


void Draw::drawNumber(int num, cv::Point& point)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }
    cv::putText(image_draw, std::to_string(num), point, cv::FONT_HERSHEY_SIMPLEX, 1.0, color);
}

void Draw::drawFloatNumber(float num, cv::Point& point)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }
    // just show one decimal digit
    std::string text = std::to_string(num);
    text = text.substr(0,3);
    cv::putText(image_draw, text, point, cv::FONT_HERSHEY_SIMPLEX, 1.0, color, 2);
}

void Draw::setDefaultColor(int value)
{
    // sets BGR color
    switch (value)
    {
        case eRED:
            color = cv::Scalar(0, 0, 255);
            break;            
        case eGREEN:
            color = cv::Scalar(0, 255, 0);
            break;
        case eBLUE:
            color = cv::Scalar(255, 0, 0);
            break;            
        case eYELLOW:
            color = cv::Scalar(0, 255, 255);
            break;
        case eWHITE:
            color = cv::Scalar(255, 255, 255);
            break;
        case eBLACK:
            color = cv::Scalar(0, 0, 0);
            break;
    }
}

}
