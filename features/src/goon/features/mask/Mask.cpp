/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/mask/Mask.h"

namespace goon 
{
namespace features
{     
// Constructor
Mask::Mask ()
{
    window2 = cv::Rect(0,0,0,0);
}

Mask::~Mask ()
{
}

// copy constructor (needed for vectors)    
Mask::Mask(const Mask& oMask) 
{
    window2 = oMask.window2;
    cloneMat(oMask.mat); // mask is cloned, not just assigned
}  

// assignment operator
Mask& Mask::operator=(const Mask& oMask)
{
    window2 = oMask.window2;
    cloneMat(oMask.mat); // mask is cloned, not just assigned
    return *this;    
}

// The given mask is roied and cloned.
void Mask::setMask(cv::Mat& mask, cv::Rect& window)
{
    cv::Mat roiMask = mask(window);   
    
    cloneMat(roiMask);
    setWindow2(window);
}

void Mask::cloneMat(const cv::Mat& mask)
{
    mat = mask.clone();    
}

void Mask::clear()
{
    mat.setTo(0);
    window2 = cv::Rect (0,0,0,0);
}

void Mask::checkOverlap(Mask& oMask2, float& overlapFraction, float& overlapFraction2)
{
    // TO DO ...
    overlapFraction = 0.0;
    overlapFraction2 = 0.0;
}

std::string Mask::toString()
{
    std::string desc = "Mask [ window = (" + 
            std::to_string(window2.x) + "," + std::to_string(window2.y) + "," + std::to_string(window2.width) + "," + std::to_string(window2.height) + ")" + "]";
    return desc;
}

}
}
							 