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
        std::mutex mutexObject;        
        cv::Mat imageCam;       // image from camera
        // retinal & peripheral section
        Retina oRetina2;          // copy of the dynamic retina
        Rois oROIs2;               // copy of the dynamic rois 
        // cortex section
        Object oObject2;        // copy of the dynamic object
        Scene oScene;
        
    public:
        VisualData();
        ~VisualData();

        // updates camera image (copies given image)
        void setCameraFrame(cv::Mat& img);
        // gets copy of camera image
        void getCameraFrameCopy(cv::Mat& imageOut);
                
        // store static copies of the dynamic data
        void updateRetina2(Retina& oRetina);
        void updateROIs2(Rois& oROIs);
        void updateObject2(Object& oObject);

        void getRetinaCopy(Retina& oRetina3);
        void getROIsCopy(Rois& oROIs3);
        void getObjectCopy(Object& oObject3);        
                
        Scene& getScene() {return oScene;};
};
}    
#endif

        