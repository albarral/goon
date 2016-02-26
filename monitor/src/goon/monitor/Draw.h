#ifndef __GOON_MONITOR_DRAW_H
#define __GOON_MONITOR_DRAW_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

namespace goon
{
// Utility class for drawing visual objects (masks, points, ellipses ...) on openCV images
class Draw
{        
public:
    enum eColor{
        eRED, 
        eGREEN,
        eBLUE,                
        eYELLOW, 
        eWHITE,
        eBLACK,
        eCOLORS
    };

private:
    cv::Scalar color;           // rgb color
    cv::Mat image_draw;     // image drawn 
    bool bsized;            // indicates that image_draw has been sized    
    
public:
    Draw();   
    
    // returns a reference to the drawn image
    cv::Mat& getOutput() {return image_draw;};
    
    // Sets the image size
    void setSize (cv::Mat& image);

    // Sets the background image to be drawn. 
    void setBackGround (cv::Mat& image);

    // Clears the image background (black image).)
    void clearBackGround ();

    // Sets the color to be used for painting
    void setExactColor(cv::Vec3f&  rgb_color);

    // Draws a mask in the image
    void drawMask (cv::Mat& mask);

    // Draws a mask (roied by a window) in the image
    void drawMask (cv::Mat& mask, cv::Rect& window);

    // Draws a point in the image with the specified color and radius (default green and 3 pixels)
    void drawPoint (cv::Point& point, int def_color = Draw::eGREEN, int radius = 3);

    // Draws an ellipse in the image
    void drawEllipse (cv::Point& center, int width, int height, int orientation);

    // Draws an horizontal line in the image
    void drawHLine (int row);

    // Draws a vertical line in the image
    void drawVLine (int col);

    // Draws a number in the image at the specified point. 
    void drawNumber (int num, cv::Point& point);
    void drawFloatNumber(float num, cv::Point& point);
    // Sets a predefined value for the color
    void setDefaultColor (int value);    
};
}
    
#endif
