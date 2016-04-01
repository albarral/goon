/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/body/Body.h"

namespace goon 
{
// Constructor
Body::Body ()
{
    window = cv::Rect(0,0,0,0);
    area = 0;
}

Body::~Body ()
{
}

// copy constructor (needed for vectors)    
Body::Body(const Body& oBody) 
{
    area = oBody.area;
    window = oBody.window;
    cloneMask(oBody.mask); // mask is cloned, not just assigned
}  

// assignment operator
Body& Body::operator=(const Body& oBody)
{
    area = oBody.area;
    window = oBody.window;
    cloneMask(oBody.mask); // mask is cloned, not just assigned
    return *this;    
}

// Fills the Body with the given mask and window (cloning the mask)    
// The given mask is roied and cloned, and it's area is computed.
void Body::setMask(cv::Mat& amask, cv::Rect& awindow)
{
    cv::Mat roiMask = amask(awindow);   
    
    cloneMask(roiMask);
    window = awindow;
    // the new mask's area is computed
    area = cv::countNonZero(mask);
}

void Body::cloneMask(const cv::Mat& mask)
{
    this->mask = mask.clone();    
}

void Body::clearBody()
{
    if (mask.rows != 0 && mask.cols != 0)            
        mask.setTo(0);
    window = cv::Rect (0,0,0,0);
}

// Checks if this mask overlaps with a second one.  
// The overlapped area fractions are returned (own overlapped area, other's overlapped area) 
bool Body::checkBodyOverlap(Body& oBody, float& overlapFraction, float& overlapFraction2)
{
    bool boverlap;
    // check intersection of windows
    cv::Rect intersectionWindow = window & oBody.window;     
    // if no intersection, no overlap
    if (intersectionWindow.width == 0)
    {
        boverlap = false;
        overlapFraction = overlapFraction2 = 0.0;
    }
    // if intersection, compare masks
    else
    {
        cv::Mat maskOverlap = mask & oBody.mask;
        int overlapArea = cv::countNonZero(maskOverlap);
        // if masks overlap, return overlapped fractions
        if (overlapArea > 0)
        {
            boverlap = true;
            overlapFraction = (float)overlapArea / area;
            overlapFraction2 = (float)overlapArea / oBody.area;
        }
        else
        {
            boverlap = false;
            overlapFraction = overlapFraction2 = 0.0;        
        }        
    }
    
    return boverlap;
}

std::string Body::toString()
{
    std::string desc = "Body [ window = (" + 
            std::to_string(window.x) + "," + std::to_string(window.y) + "," + std::to_string(window.width) + "," + std::to_string(window.height) + ")" + 
            " area = " + std::to_string(area) + "]";
    return desc;
}

}
							 