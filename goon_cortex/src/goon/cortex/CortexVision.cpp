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
    
    oRoisDetection.detectROIs(*pRetina, *pROIs, millis);
        
    LOG4CXX_DEBUG(logger, "rois = " << pROIs->getNumROIs() << ", eliminated = " << oRoisDetection.getEliminations());

    storage[0] += pRetina->getNumRegions();
    storage[1] += pROIs->getNumROIs();
    storage[2] += 0;
    storage[3] += oRoisDetection.getEliminations();
    counter++;
    
    LOG4CXX_TRACE(logger, "update - end");
}


void CortexVision::describeROIs()
{
    LOG4CXX_DEBUG(logger, "ROIs description ...");
    for (ROI& oROI: pROIs->getList()) 
    {
        LOG4CXX_DEBUG(logger, oROI.toString());
    } 
}


}

