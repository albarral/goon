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
        cv::Mat image_cam;
        int frame_num;
        std::mutex mutex_img;
        Retina oRetina;
        Rois oROIs;        
        
    public:
        VisualData();
        ~VisualData();
                
        void newFrame(cv::Mat image);
        
        cv::Mat& getImageCam();
        
        int getFrameNum();
        
        Retina& getRetina() {return oRetina;};

        Rois& getROIs() {return oROIs;};          
        
};
}    
#endif
