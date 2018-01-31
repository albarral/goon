#ifndef __GOON_DATA_COLORBODY_H
#define __GOON_DATA_COLORBODY_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"

#include "goon/features/Body.h"

namespace goon 
{
// This class represents a 2D color body. 
// The body's color is represented by a grid of local color values.
// Extends from Body
 class ColorBody : public Body
{
 protected:
     cv::Mat massGrid;       // single channel grid representing the body's mass (16SC1)
     cv::Mat rgbGrid;       //  3 channel grid representing the body's color (32FC3)
     cv::Rect gridWindow;

 public:
    ColorBody();

    cv::Mat& getMassGrid() {return massGrid;}             
    cv::Mat& getRGBGrid() {return rgbGrid;}             
    cv::Rect& getGridWindow() {return gridWindow;};

    // sets the mass grid (cloning the input)
    void setMassGrid (const cv::Mat& grid);
    // sets the color grid (cloning the input)
    void setRGBGrid (const cv::Mat& grid);
    // sets the grid window
    void setGridWindow(cv::Rect window) {gridWindow = window;};    

    // copy constructor 
    ColorBody(const ColorBody& oColorBody);  
    // assignment operator 
    ColorBody& operator=(const ColorBody& oColorBody);
    
    // merges with another ColorBody
    virtual void merge(ColorBody& oColorBody);
    // computes the body mean rgb color (mean of all color nodes)
    cv::Vec3f computeMeanColor();    
    
    virtual std::string toString();
    virtual std::string shortDesc();    
};  

}  
#endif
