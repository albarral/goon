/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/cortex/CortexVision.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr CortexVision::logger(Logger::getLogger("goon.cortex"));
	
// constructor
CortexVision::CortexVision()
{
    pRetina = 0;
    pROIs = 0;
//    pScene = 0;
}

//CortexVision::~CortexVision ()
//{
//}

void CortexVision::init(Retina& oRetina, Rois& oROIs, Scene& oScene)
{
    pRetina = &oRetina;
    pROIs = &oROIs;    
//    pScene = &oScene;
}


void CortexVision::formObject(int focusedROI)
{
    LOG4CXX_TRACE(logger, "CortexVision.formObject");
    
    ROI* pROI = pROIs->getROIByID(focusedROI);

    if (pROI != 0)
    {
        LOG4CXX_TRACE(logger, "formObject: " + pROI->shortDesc());    

        oBinding.formObject(oObject, pRetina, pROI->getWindow());

        LOG4CXX_TRACE(logger, "cortex: " << oObject.shortDesc());
    }
    // skip if ROI doesn't exist
    else
    {
        // clear object
        oObject.clear();
        LOG4CXX_WARN(logger, "formObject skipped, ROI not found");            
    }
}


void CortexVision::analyseObject()
{
    LOG4CXX_TRACE(logger, "CortexVision.analyseObject");

    if (oObject.getMass() > 0)
    {
        oCharacterization.checkGlobalObject(oObject);    
        oCharacterization.checkObjectDetails(oObject);
    }
    // skip if empty object
    else
        LOG4CXX_WARN(logger, "formObject skipped, ROI not found");            
}
}

