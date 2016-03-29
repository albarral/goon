#ifndef __GOON_FEATURES_MASK_H
#define __GOON_FEATURES_MASK_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"

namespace goon 
{
namespace features
{     
// This class represents a 2D mask (a 1 channel image) with a specific location in the image.
// The location is given by the window member.
 class Mask
{
 private:
     cv::Mat mat;       
     cv::Rect window2;

 public:
    Mask();
    ~Mask();

    // copy constructor (needed for vectors)
    Mask(const Mask& oMask);  
    // assignment operator
    Mask& operator=(const Mask& oMask);

    // creates the Mask object from a given mask and window (cloning the matrix)    
    void setMask(cv::Mat& mask, cv::Rect& window);    

    cv::Mat& getMat() {return mat;}             
    cv::Rect& getWindow2() {return window2;};
    void setWindow2(cv::Rect& awindow) {window2 = awindow;};

    // clears the mask
    void clear();

    // checks if this mask overlaps with a second one
    // the overlapped area fractions are returned (own overlapped area, other's overlapped area) 
    void checkOverlap(Mask& oMask2, float& overlapFraction, float& overlapFraction2);
    
    std::string toString();
    
 private:
    // clones the matrix
    void cloneMat (const cv::Mat& mask);
     
};  

}
}  
#endif
