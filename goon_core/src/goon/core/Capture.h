#ifndef __GOON_CORE_CAPTURE_H
#define __GOON_CORE_CAPTURE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include "opencv2/core/core.hpp"

namespace goon 
{
// Class used to store camera captured images.
class Capture
{
    private:
        std::mutex mutex;
        cv::Mat image;       // image from camera
        int frameNum;       // frame number  
        
    public:
        Capture();
        ~Capture();
                
        // updates the image and frame number (making a copy of the given image)
        void newFrame(cv::Mat& img);
        
        cv::Mat& getImage();
        
        void getImageCopy(cv::Mat& imageOut);
        
        int getFrameNum();
};
}    
#endif
