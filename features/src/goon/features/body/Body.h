#ifndef __GOON_FEATURES_BODY_H
#define __GOON_FEATURES_BODY_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"

namespace goon 
{
// This class represents a 2D body. 
// It is represented by the following elements: 
// a mask
// a window (which defines its location in the image)
 class Body
{
 private:
     cv::Mat mask;       
     cv::Rect window;
     int area;  // pixels inside the mask

 public:
    Body();
    ~Body();

    // copy constructor (needed for vectors)
    Body(const Body& oBody);  
    // assignment operator
    Body& operator=(const Body& oBody);

    // fills the Body with the given mask and window (cloning the mask)    
    void setMask(cv::Mat& mask, cv::Rect& window);    
    cv::Mat& getMask() {return mask;}             
    cv::Rect& getWindow() {return window;};
    int getArea() {return area;}

    // clears the mask
    void clearBody();

    // Checks if this mask overlaps with a second one.  
    // The overlapped area fractions are returned (own overlapped area, other's overlapped area) 
    bool checkBodyOverlap(Body& oBody, float& overlapFraction, float& overlapFraction2);
    
    virtual std::string toString();
    
 private:
    // clones the matrix
    void cloneMask (const cv::Mat& mask);
    void setWindow(cv::Rect& awindow) {window = awindow;};
     
};  

}  
#endif
