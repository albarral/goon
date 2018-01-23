#ifndef __GOON_CORE_VISUAL_DATA_H
#define __GOON_CORE_VISUAL_DATA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

#include "opencv2/core/core.hpp"
#include "goon/data/retina.h"
#include "goon/data/rois.h"
#include "goon/data/cortex/Object.h"
#include "goon/data/cortex/Scene.h"

namespace goon 
{
class VisualData
{
    private:
        std::mutex mutexCam;        
        std::mutex mutexRetina;        
        std::mutex mutexRois;        
        cv::Mat imageCam;       // image from camera
        // dynamic data (in constant change)
        Retina oRetina;             // retinal data (output of retinal vision)
        Rois oROIs;                  // regions of interest (output of peripheral vision)
        // static data (copy of the dynamic data after each see loop)
        Retina oRetina2;          // copy of the dynamic retina
        Rois oROIs2;               // copy of the dynamic rois 
        // cortex section
        Object oObject;
        Scene oScene;
        
    public:
        VisualData();
        ~VisualData();

        // updates camera image (copies given image)
        void setCameraFrame(cv::Mat& img);
        // gets copy of camera image
        void getCameraFrameCopy(cv::Mat& imageOut);
                
        Retina& getRetina() {return oRetina;};
        Rois& getROIs() {return oROIs;};
        Retina& getRetina2();
        Rois& getROIs2();
                
        Object& getObject() {return oObject;};
        Scene& getScene() {return oScene;};

        // store static copies of the dynamic data
        void cloneRetina();
        void cloneROIs();
                
};
}    
#endif

        