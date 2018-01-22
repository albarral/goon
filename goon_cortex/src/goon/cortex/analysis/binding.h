#ifndef __GOON_CORTEX_BINDING_H
#define __GOON_CORTEX_BINDING_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/core/core.hpp>
#include "goon/cortex/data/retinal_center.h"
#include "goon/cortex/data/visual_center.h"


namespace goon
{
class Binding
{
private:
    RetinalCenter* mRetinalCenter;
    VisualCenter* mVisualCenter;
    Landmark* oLandmark;
    float joinObjectFraction;

public:
    Binding (RetinalCenter* oRetinalCenter, VisualCenter* oVisualCenter);
    ~Binding();
  
 		
    void formObject (CvRect* roi_window);
    // This function builds the global landmark from the specified list of retinal regions.
    // The landmark's mask is built and its global features are computed. 	     
 };
}
#endif
