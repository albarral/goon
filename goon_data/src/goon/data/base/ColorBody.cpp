/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/ColorBody.h"

namespace goon 
{
// Constructor
ColorBody::ColorBody ()
{
    gridWindow = cv::Rect(0,0,0,0);
}

// copy constructor 
ColorBody::ColorBody(const ColorBody& oColorBody) : Body(oColorBody)
{
    gridWindow = oColorBody.gridWindow;
    // grids are cloned
    if (!oColorBody.massGrid.empty())
        massGrid = oColorBody.massGrid.clone(); 
    if (!oColorBody.rgbGrid.empty())
        rgbGrid = oColorBody.rgbGrid.clone(); 
}  

// assignment operator 
ColorBody& ColorBody::operator=(const ColorBody& oColorBody)
{
    Body::operator=(oColorBody);
    
    gridWindow = oColorBody.gridWindow;
    // grids are cloned
    if (!oColorBody.massGrid.empty())
        massGrid = oColorBody.massGrid.clone(); 
    if (!oColorBody.rgbGrid.empty())
        rgbGrid = oColorBody.rgbGrid.clone(); 

    return *this;    
}


void ColorBody::setMassGrid(const cv::Mat& grid)
{
    massGrid = grid.clone();
}


void ColorBody::setRGBGrid(const cv::Mat& grid)
{ 
    rgbGrid = grid.clone();
}


cv::Vec3f ColorBody::computeMeanColor()
{    
    // roi both grids
    cv::Mat massGridROI = massGrid(gridWindow);
    cv::Mat rgbGridROI = rgbGrid(gridWindow);
    
    // convert mass grid to mask
    cv::Mat maskMass;
    massGridROI.convertTo(maskMass, CV_8UC1);

    // and compute mean color
    cv::Scalar color = cv::mean(rgbGridROI, maskMass);    
    cv::Vec3f rgbColor = cv::Vec3f(color[0], color[1], color[2]);
    return rgbColor;
}


void ColorBody::merge(ColorBody& oColorBody)
{
    // merge body part
    Body::merge(oColorBody);
    
    // compute union of windows
    gridWindow = gridWindow | oColorBody.gridWindow;    

    // roi body grids
    cv::Mat massGridROI = massGrid(gridWindow);
    cv::Mat rgbGridROI = rgbGrid(gridWindow);
    // roi body2 grids
    cv::Mat massGrid2ROI = oColorBody.massGrid(gridWindow);
    cv::Mat rgbGrid2ROI = oColorBody.rgbGrid(gridWindow);

    // add mass grids
    massGridROI += massGrid2ROI;
    // average of color grids
    rgbGridROI += rgbGrid2ROI;
    rgbGridROI = 0.5 * rgbGridROI;
}

}
							 