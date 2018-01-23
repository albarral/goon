#ifndef __GOON_CORTEX_VISION_H
#define __GOON_CORTEX_VISION_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/data/retina.h"
#include "goon/data/rois.h"
#include "goon/data/cortex/Object.h"
#include "goon/data/cortex/Scene.h"
#include "goon/cortex/analysis/binding.h"
#include "goon/cortex/analysis/characterization.h"
//#include "goon/cortex/recognition/recognition.h"

namespace goon
{
class CortexVision
{
private:
    static log4cxx::LoggerPtr logger;
    Retina* pRetina;
    Rois* pROIs;
    Scene* pScene;
    Object oObject;
    Binding oBinding;
    Characterization oCharacterization;
    //Recognition oRecognition;

public:
    CortexVision();
    //~CortexVision();

    // Initializes the module 
    void init(Retina& oRetina, Rois& oROIs, Scene& oScene);

    // it does the object binding process starting from the given focused ROI
    void formObject(int focusedROI);
       
    // it performs a characterization of the formed object, analyzing it in detail
    void analyseObject();    
    
    // if performs the object recognition process (comparing it with a all stored models in memory)
    //void identifyObject();        
};

}  	

#endif
