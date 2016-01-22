/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include <string>

#include "draw.h"

using namespace cv;

namespace goon
{
// Constructor
Draw::Draw ()
{    
    color = Scalar(255, 255, 255);  // white
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
        
    image_draw.setTo(Scalar(0));
}


void Draw::setExactColor(Vec3f& rgb_color)
{
    color = Scalar(rgb_color[2], rgb_color[1], rgb_color[0]);      // BGR
}


void Draw::drawMask(Mat& mask)
{                
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    image_draw.setTo(color, mask);
}


void Draw::drawMask(Mat& mask, Rect& window)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    Mat image_roi = image_draw(window);
    image_roi.setTo(color, mask);
}


void Draw::drawPoint(Point& point, int def_color, int radius)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    setDefaultColor (def_color);    
    circle(image_draw, point, radius, color, -1);
}


void Draw::drawEllipse(Point& center, int width, int height, int orientation)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }
    
    setDefaultColor (eYELLOW);       
    ellipse (image_draw, center, Size(width, height), orientation, 0, 360, color, 3);
}


void Draw::drawHLine(int row)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    Point pt1(0, row);
    Point pt2(image_draw.cols-1, row);
    line(image_draw, pt1, pt2, color);    
}

        
void Draw::drawVLine(int col)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }

    Point pt1(col, 0);
    Point pt2(col, image_draw.rows-1);
    line(image_draw, pt1, pt2, color);    
}


void Draw::drawNumber(int num, cv::Point& point)
{
    if (!bsized)
    {
        std::cout << "Draw error: image_draw still not created" << std::endl;
        return;
    }
    putText(image_draw, std::to_string(num), point, FONT_HERSHEY_SIMPLEX, 1.0, color);
}


void Draw::setDefaultColor(int value)
{
    // sets BGR color
    switch (value)
    {
        case eRED:
            color = Scalar(0, 0, 255);
            break;            
        case eGREEN:
            color = Scalar(0, 255, 0);
            break;
        case eBLUE:
            color = Scalar(255, 0, 0);
            break;            
        case eYELLOW:
            color = Scalar(0, 255, 255);
            break;
        case eWHITE:
            color = Scalar(255, 255, 255);
            break;
        case eBLACK:
            color = Scalar(0, 0, 0);
            break;
    }
}

}
