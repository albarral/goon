#ifndef __GOON_DATA_VISUAL_DATA_H
#define __GOON_DATA_VISUAL_DATA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"
#include "goon/data/retina.h"
#include "goon/data/rois.h"

namespace goon 
{
class VisualData
{
    private:
        Retina oRetina;             // dynamic retina   
        //Retina oRetina2;          // static retina
        Rois oROIs;                   // regions of interest (output of peripheral vision module)
        
    public:
        VisualData();
        ~VisualData();
                
        Retina& getRetina() {return oRetina;};

        Rois& getROIs() {return oROIs;};          
        
};
}    
#endif
