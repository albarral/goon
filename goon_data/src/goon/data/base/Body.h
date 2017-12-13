#ifndef __GOON_DATA_BODY_H
#define __GOON_DATA_BODY_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"

#include "goon/data/base/blob.h"

namespace goon 
{
// This class represents a 2D body. 
// It is represented by the following elements: 
// a mask
// a window 
// Extends from Blob
 class Body : public Blob
{
 private:
     cv::Mat mask;       
     cv::Rect window;

 public:
    Body();

    cv::Mat& getMask() {return mask;}             
    cv::Rect& getWindow() {return window;};

    // copy constructor (needed for mask)
    Body(const Body& oBody);  
    // assignment operator (needed for mask)
    Body& operator=(const Body& oBody);

    // fills the Body with the given mask and window (cloning the mask)    
    void setMaskAndWindow(cv::Mat& mask, cv::Rect& window);    

    void clear();
    void computeMass();
    void computeBlob();
    
    // merges with another Body
    virtual void merge(Body& oBody);

    // Checks if this body overlaps with the given one (computing the intersection of their masks)
    // The overlapped area (pixels) is returned.
    int computeOverlap(Body& oBody);
    
    virtual std::string toString();
         
};  

}  
#endif
