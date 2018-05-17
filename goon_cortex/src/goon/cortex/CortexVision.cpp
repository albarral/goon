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
}

//CortexVision::~CortexVision ()
//{
//}

void CortexVision::formObject(Object& oObject, int focusedROI)
{
    LOG4CXX_TRACE(logger, "CortexVision.formObject");
    
    ROI* pROI = oROIs3.getROIByID(focusedROI);

    if (pROI != 0)
    {
        LOG4CXX_TRACE(logger, "formObject: " + pROI->shortDesc());    

        oBinding.formObject(oRetina3, pROI->getWindow(), oObject);
    }
    // skip if ROI doesn't exist
    else
    {
        // clear object
        oObject.clear();
        LOG4CXX_WARN(logger, "formObject skipped, ROI not found");            
    }
}


void CortexVision::modelObject(Object& oObject)
{
    LOG4CXX_TRACE(logger, "CortexVision.modelObject");

    if (oObject.getMass() > 0)
    {
        // global & local characterization
        oCharacterization.checkGlobalObject(oObject);    
        oCharacterization.checkObjectDetails(oObject);
        
        // object modelling
        oModeling.modelObject(oObject, oObjectModel);    
        LOG4CXX_DEBUG(logger, oObjectModel.shortDesc());
    }
    // skip if empty object
    else
        LOG4CXX_WARN(logger, "analyseObject skipped, no object detected");            
}

bool CortexVision::checkEvidence(Object& oObject)
{
    LOG4CXX_TRACE(logger, "CortexVision.checkEvidence");

    if (oObject.getMass() > 0)
    {
        if (oEvidence.checkSelfEvidence(oObjectModel))
        {
            LOG4CXX_INFO(logger, "evidence ok"); 
            return true;
        }
        else
        {
            LOG4CXX_INFO(logger, "evidence failed"); 
            return false;            
        }
    }
    else
        return false;
}

bool CortexVision::identifyObject(Object& oObject)
{
    LOG4CXX_TRACE(logger, "CortexVision.identifyObject");

    if (oObject.getMass() > 0)
    {
        if (oRecognition.recogniseObject(oObjectModel))
        {
            LOG4CXX_INFO(logger, "object recognized"); 
            return true;
        }
        else
        {
            LOG4CXX_INFO(logger, "object not recognized"); 
            return false;            
        }
    }
    else
        return false;
}

void CortexVision::memorizeObject()
{
    LOG4CXX_TRACE(logger, "CortexVision.memorizeObject");

    if (oObjectModel.getMass() > 0)
    {
        LOG4CXX_INFO(logger, "new object"); 
        oRecognition.learnModel(oObjectModel);        
    }        
}

}

