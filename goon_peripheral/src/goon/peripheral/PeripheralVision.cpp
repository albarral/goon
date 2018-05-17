/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/peripheral/PeripheralVision.h"
#include <goon/features/shape/shape.h>
#include <goon/features/color/rgb_color.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr PeripheralVision::logger(Logger::getLogger("goon.peripheral"));
	
// constructor
PeripheralVision::PeripheralVision()
{
    counter = 0;	
    for (int i=0; i<4; i++)            
        storage[i] = 0;
}

// destructor
PeripheralVision::~PeripheralVision ()
{
    float averages[4];				
    if (counter != 0)
    {
        for (int i=0; i<4; i++)
                averages[i] = (float)storage[i] / counter;        
    }

    LOG4CXX_TRACE(logger, "Peripheral vision averages: ");
    LOG4CXX_TRACE(logger, "regions = " << averages[0] << ", units = " << averages[1] << ", merges = " << averages[2] << ", eliminations = " << averages[3]);
}

void PeripheralVision::setParameters (int same_RGB, int similar_RGB)
{
     RGBColor::setTolerances(same_RGB, similar_RGB);
}


// This function implements the peripheral vision process.
// It samples the retinal map to discover and track regions of interest in the visual scene. 	
void PeripheralVision::update(Retina& oRetina, int millis)
{
    LOG4CXX_TRACE(logger, "update - init");
    
    oRoisDetection.detectROIs(oRetina, oROIs, millis);
        
    LOG4CXX_DEBUG(logger, "rois = " << oROIs.getNumROIs() << ", eliminated = " << oRoisDetection.getEliminations());

    storage[0] += oRetina.getNumRegions();
    storage[1] += oROIs.getNumROIs();
    storage[2] += 0;
    storage[3] += oRoisDetection.getEliminations();
    counter++;
    
    LOG4CXX_TRACE(logger, "update - end");
}


void PeripheralVision::describeROIs()
{
    LOG4CXX_DEBUG(logger, "ROIs description ...");
    for (ROI& oROI: oROIs.getList()) 
    {
        LOG4CXX_DEBUG(logger, oROI.toString());
    } 
}


}

