#ifndef __GOON_DATA_VCOLOR_H
#define __GOON_DATA_VCOLOR_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/core/core.hpp>

namespace goon 
{
 class vColor
{     
 private:
        cv::Vec3i hsv;    
        cv::Vec3i hsv_dev;    
        cv::Vec3i rgb;    
        cv::Vec3i rgb_dev;    

 public:
//     vColor ();
//     ~vColor();

    cv::Vec3i& getHSV() {return hsv;}
    cv::Vec3i& getHSVdev() {return hsv_dev;}
    cv::Vec3i& getRGB() {return rgb;}
    cv::Vec3i& getRGBdev() {return rgb_dev;}
    
    void setHSV(cv::Vec3i& hsv) {this->hsv=hsv;}    
    void setHSVDev(cv::Vec3i& hsv_dev) {this->hsv_dev=hsv_dev;}    
    void setRGB(cv::Vec3i& rgb) {this->rgb=rgb;}    
    void setRGBDev(cv::Vec3i& rgb_dev) {this->rgb_dev=rgb_dev;}    
};  
}  
#endif
