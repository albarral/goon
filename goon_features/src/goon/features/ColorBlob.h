#ifndef __GOON_FEATURES_COLORBLOB_H
#define __GOON_FEATURES_COLORBLOB_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>

#include "goon/features/Blob.h"

namespace goon 
{
// This class represents a color blob. A blob with color info.
class ColorBlob : public Blob
{
protected:
    cv::Vec3f rgb_color;     // color in RGB space
    cv::Vec3f hsv_color;     // color in HSV space

public:
    ColorBlob();
    
    cv::Vec3f& getRGB() {return rgb_color;};
    cv::Vec3f& getHSV() {return hsv_color;};
    
    void setRGB(cv::Vec3f color) {rgb_color = color;};
    void setHSV(cv::Vec3f color) {hsv_color = color;};
   
    // merges with another blob
    virtual void merge(ColorBlob& oColorBlob2);
    
    // returns all blob values in string form
    virtual std::string toString();
    virtual std::string shortDesc();    
 }; 
}

#endif
