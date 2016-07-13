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
        std::mutex mutex1;        
        std::mutex mutex2;        
        // dynamic data (in constant change)
        Retina oRetina;             // retinal data (output of retinal vision)
        Rois oROIs;                  // regions of interest (output of peripheral vision)
        // static copy of the dynamic data (updated after each visual iteration)
        Retina oRetina2;          // copy of the dynamic retina
        Rois oROIs2;               // copy of the dynamic rois 
        
    public:
        VisualData();
        ~VisualData();
                
        Retina& getRetina() {return oRetina;};
        Rois& getROIs() {return oROIs;};
        
        // store static copies of the dynamic data
        void storeRetinaPhoto();
        void storeROIsPhoto();
        
        Retina& getRetina2();
        Rois& getROIs2();
        
};
}    
#endif

        