#ifndef __GOON_CORTEX_VISION_H
#define __GOON_CORTEX_VISION_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/data/retina.h"
#include "goon/data/rois.h"
//#include "goon/data/VisualMemory.h"
#include "goon/data/cortex/Object.h"
#include "goon/data/cortex/ObjectModel.h"
#include "goon/cortex/bind/binding.h"
#include "goon/cortex/model/characterization.h"
#include "goon/cortex/model/Modeling.h"
#include "goon/cortex/recognition/Recognition2.h"

namespace goon
{
class CortexVision
{
private:
    static log4cxx::LoggerPtr logger;
    Retina oRetina3;
    Rois oROIs3;
    Object oObject;
    ObjectModel oObjectModel;   // result of modeling the object
//    VisualMemory oVisualMemory;
    Binding oBinding;
    Characterization oCharacterization;
    Modeling oModeling;     // class for modeling objects    
    Recognition2 oRecognition;

public:
    CortexVision();
    //~CortexVision();

    Retina& getRetina() {return oRetina3;};
    Rois& getROIs() {return oROIs3;};    
    Object& getObject() {return oObject;}
    
    // it does the object binding process starting from the given focused ROI
    void formObject(int focusedROI);
       
    // it performs a characterization of the formed object, analyzing it in detail
    void analyseObject();    
    
    // if performs the object recognition process (comparing it with a all stored models in memory)
    void identifyObject();        
};

}  	

#endif
