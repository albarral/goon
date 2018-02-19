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
#include "goon/data/cortex/ObjectModel.h"
#include "goon/cortex/bind/binding.h"
#include "goon/cortex/model/characterization.h"
#include "goon/cortex/model/Modeling.h"
#include "goon/cortex/recognition/Evidence.h"
#include "goon/cortex/recognition/Recognition2.h"

namespace goon
{
class CortexVision
{
private:
    static log4cxx::LoggerPtr logger;
    Retina oRetina3;
    Rois oROIs3;
    ObjectModel oObjectModel;    // modeled object
    Binding oBinding;
    Characterization oCharacterization;
    Modeling oModeling;     
    Evidence oEvidence;
    Recognition2 oRecognition;

public:
    CortexVision();
    //~CortexVision();

    Retina& getRetina() {return oRetina3;};
    Rois& getROIs() {return oROIs3;};    
    
    // forms the object binding regions around the given ROI
    void formObject(Object& oObject, int focusedROI);
       
    // models the object doing a characterization (global & local) and modeling process
    void modelObject(Object& oObject);    
    
    // checks that the looked object is still the same
    bool checkEvidence(Object& oObject);        

    // performs the object recognition process (comparing it models in memory)
    bool identifyObject(Object& oObject);        

    // memorizes the object storing its model in visual memory
    void memorizeObject();        
};

}  	

#endif
