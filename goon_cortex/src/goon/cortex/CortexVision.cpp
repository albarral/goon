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
    pScene = 0;
}

//CortexVision::~CortexVision ()
//{
//}

void CortexVision::init(Retina& oRetina, Rois& oROIs, Scene& oScene)
{
    pRetina = &oRetina;
    pROIs = &oROIs;    
    pScene = &oScene;
}


void CortexVision::formObject(int focusedROI)
{
    LOG4CXX_TRACE(logger, "CortexVision.formObject");
    
    ROI& oROI = pROIs->getROI(focusedROI);
    
    oBinding.formObject(oObject, pRetina, oROI.getWindow());
    
    LOG4CXX_DEBUG(logger, "cortex: " << oObject.shortDesc());
}


void CortexVision::analyseObject()
{
    LOG4CXX_TRACE(logger, "CortexVision.analyseObject");
    
    oCharacterization.checkGlobalObject(oObject);
    
    oCharacterization.checkObjectDetails(oObject);
}


}

