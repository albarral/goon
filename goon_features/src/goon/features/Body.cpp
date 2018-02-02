/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/Body.h"
#include "goon/features/shape/shape.h"

namespace goon 
{
// Constructor
Body::Body ()
{
    window = cv::Rect(0,0,0,0);
}

// copy constructor (needed for mask)    
Body::Body(const Body& oBody) : ColorBlob(oBody)
{
    window = oBody.window;
    // mask is cloned, not just assigned
    if (!oBody.mask.empty())
        mask = oBody.mask.clone(); 
}  

// assignment operator (needed for mask)
Body& Body::operator=(const Body& oBody)
{
    ColorBlob::operator=(oBody);
    
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
    // assure that given window lies inside of given mask
    assert(amask.rows >= awindow.y+awindow.height);
    assert(amask.cols >= awindow.x+awindow.width);
    
    window = awindow;
    if (!amask.empty())
    {    
        // the body's mask is reduced to fit in the given window
        cv::Mat roiMask = amask(awindow);       
        mask = roiMask.clone(); 
    }
}

void Body::clear()
{
    Blob::clear();
    
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

void Body::computeShape()
{
    Shape oShape;
    oShape.computeShapeFromCovs(covs);
    
    shapeFactor = oShape.getShapeFactor();
    orientation = oShape.getAngle();    
}

cv::Mat Body::computeBorderMask()
{
    cv::Mat maskBorder = mask == Body::BORDER_VALUE;
    return maskBorder;    
}


void Body::merge(Body& oBody)
{
    // merge color blob part
    ColorBlob::merge(oBody);
    
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


int Body::computeOverlap(cv::Mat& maskB, cv::Rect& windowB)
{
    int pixelsShared = 0;
    
    // intersection of windows
    cv::Rect intersection = window & windowB;     
    // if windows intersect, compare masks
    if (intersection.width > 0)  
    {
        // translate intersection window (in camera coordinates) to local coordinate systems of both bodies
        cv::Rect window1 = intersection - cv::Point(window.x, window.y);
        cv::Rect window2 = intersection - cv::Point(windowB.x, windowB.y);
        cv::Mat mask1 = mask(window1);
        cv::Mat mask2 = maskB(window2);
        // intersection of masks
        cv::Mat maskOverlap = mask1 & mask2;
        // area of intersection
        pixelsShared = cv::countNonZero(maskOverlap);
    }
    
    return pixelsShared;
}

int Body::computeOverlap(Body& oBody)
{
    return computeOverlap(oBody.mask, oBody.window);
}


std::string Body::toString()
{
    std::string desc = "Body [ window = (" + 
            std::to_string(window.x) + "," + std::to_string(window.y) + "," + std::to_string(window.width) + "," + std::to_string(window.height) + ") - " + 
            ColorBlob::toString() + "]";
    return desc;
}

std::string Body::shortDesc()
{
    std::string desc = "Body [ window = (" + 
            std::to_string(window.x) + "," + std::to_string(window.y) + "," + std::to_string(window.width) + "," + std::to_string(window.height) + ") - " + 
            ColorBlob::shortDesc() + "]";
    return desc;
}

}
							 