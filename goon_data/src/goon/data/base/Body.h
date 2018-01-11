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
 public:
    static const int BODY_VALUE = 255;
    static const int BORDER_VALUE = 1;
     
 protected:
     cv::Mat mask;       // body mask
     cv::Rect window;   // body window in image

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
    cv::Mat computeBorderMask();
    
    // merges with another Body
    virtual void merge(Body& oBody);

    // computes the body's overlapped surface with a given mask (and window)
    int computeOverlap(cv::Mat& maskB, cv::Rect& windowB);

    // computes the body's overlapped surface with another body (the intersection of both masks)
    // the overlapped area (pixels) is returned
    int computeOverlap(Body& oBody);
        
    virtual std::string toString();
    virtual std::string shortDesc();             
    
};  

}  
#endif
