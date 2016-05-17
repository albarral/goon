/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/Body.h"
#include "goon/utils/shape.h"

namespace goon 
{
// Constructor
Body::Body ()
{
    window = cv::Rect(0,0,0,0);
}

// copy constructor (needed for mask)    
Body::Body(const Body& oBody) : Blob(oBody)
{
    window = oBody.window;
    // mask is cloned, not just assigned
    if (!oBody.mask.empty())
        mask = oBody.mask.clone(); 
}  

// assignment operator (needed for mask)
Body& Body::operator=(const Body& oBody)
{
    Blob::operator=(oBody);
    
    window = oBody.window;
    // mask is cloned, not just assigned
    if (!oBody.mask.empty())
        mask = oBody.mask.clone(); 
    return *this;    
}

// Fills the Body with the given mask and window 
// The given mask is roied and cloned
void Body::setMaskAndWindow(cv::Mat& amask, cv::Rect& awindow)
{
    assert(amask.rows >= awindow.y+awindow.height);
    assert(amask.cols >= awindow.x+awindow.width);
    
    window = awindow;
    if (!amask.empty())
    {    
        // make roi of mask before cloning it
        cv::Mat roiMask = amask(awindow);       
        mask = roiMask.clone(); 
    }
}

void Body::clear()
{
    if (!mask.empty())            
        mask.setTo(0);
    window = cv::Rect (0,0,0,0);
}

// new mask's area is computed
void Body::computeMass()
{
    mass = cv::countNonZero(mask);    
}

void Body::computeBlob()
{
    Shape::computeCovariances(mask, window, pos, covs);
}

void Body::merge(Body& oBody)
{
    // merge blob part
    Blob::merge(oBody);
    
    // get windows union 
    cv::Rect windowBig = window | oBody.window;     
    // new bigger mask (empty)
    cv::Mat maskBig = cv::Mat::zeros(windowBig.height, windowBig.width, CV_8UC1); 
    // adapt windows to new mask limits
    cv::Point newOrigin = cv::Point2i(windowBig.x, windowBig.y);
    cv::Rect window1 = window - newOrigin;
    cv::Rect window2 = oBody.window - newOrigin;
    
    // fill mask with first body (direct copy)
    cv::Mat maskRoi1 = maskBig(window1);    
    mask.copyTo(maskRoi1);
    
    // fill mask with second body (logical or)
    cv::Mat maskRoi2 = maskBig(window2);        
    maskRoi2 = maskRoi2 | oBody.mask;
    
    // finally update new values
    mask = maskBig;
    window = windowBig;
}


int Body::computeOverlap(Body& oBody)
{
    int pixelsShared = 0;
    
    // intersection of windows
    cv::Rect intersectionWindow = window & oBody.window;     
    // if windows intersect, compare masks
    if (intersectionWindow.width > 0)  
    {
        // intersection of masks
        cv::Mat maskOverlap = mask & oBody.mask;
        // area of intersection
        pixelsShared = cv::countNonZero(maskOverlap);
    }
    
    return pixelsShared;
}


std::string Body::toString()
{
    std::string desc = "Body [ window = (" + 
            std::to_string(window.x) + "," + std::to_string(window.y) + "," + std::to_string(window.width) + "," + std::to_string(window.height) + ")" + 
            Blob::toString() + "]";
    return desc;
}

}
							 