#ifndef __GOON_MAIN_TESTIMAGE_H
#define __GOON_MAIN_TESTIMAGE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/opencv.hpp"

namespace goon
{    
class TestImage
{
private:
    int w; 
    int h;
    cv::Mat imageCam;
    cv::Mat imageHSV;        
    cv::Mat maskSegmented;    

public:
        TestImage();
                
        int getW() {return w;};
        int getH() {return h;};                
        cv::Mat getImageCam() {return imageCam;};
        cv::Mat getImageHSV() {return imageHSV;};
        cv::Mat getMaskSegmented() {return maskSegmented;};

        // create artificial image
        void createImage(int w, int h);        
        // load existing image
        bool loadImage();
};

}    
#endif
