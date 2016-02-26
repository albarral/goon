#ifndef __GOON_DATA_VISUAL_DATA_H
#define __GOON_DATA_VISUAL_DATA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

#include "opencv2/core/core.hpp"
#include "goon/data/retina.h"
#include "goon/data/rois.h"

namespace goon 
{
class VisualData
{
    private:
        std::mutex mutex_img;
        cv::Mat imageCam;       // image from camera
        int frame_num;             // frame number  
        Retina oRetina;             // dynamic retina   
        //Retina oRetina2;          // static retina
        Rois oROIs;        
        
    public:
        VisualData();
        ~VisualData();
                
        // updates the imageCam and frame number (making a copy of the given image)
        void newFrame(cv::Mat& image);
        
        cv::Mat& getImageCam();
        
        void getCopyImageCam(cv::Mat& imageOut);
        
        int getFrameNum();
        
        Retina& getRetina() {return oRetina;};

        Rois& getROIs() {return oROIs;};          
        
};
}    
#endif
