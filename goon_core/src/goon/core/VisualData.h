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
        Scene oScene;
        Object oObject2;        // copy of the dynamic object
        
    public:
        VisualData();
        ~VisualData();

        // updates camera image (copies given image)
        void setCameraFrame(cv::Mat& img);
        // gets copy of camera image
        void getCameraFrameCopy(cv::Mat& imageOut);
                
        Scene& getScene() {return oScene;};

//        Retina& getRetina2();
//        Rois& getROIs2();                
        Object& getObject2();

        // store static copies of the dynamic data
        void updateRetina(Retina& oRetina);
        void updateROIs(Rois& oROIs);
        void getRetinaCopy(Retina& oRetina3);
        void getROIsCopy(Rois& oROIs3);

        void cloneObject(Object& oObject);
        
                
};
}    
#endif

        