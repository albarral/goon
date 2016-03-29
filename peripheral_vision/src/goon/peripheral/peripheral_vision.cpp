/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "goon/peripheral/peripheral_vision.h"
#include <goon/data/goon_version.h>
#include <goon/utils/shape.h>
#include <goon/utils/rgb_color.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr PeripheralVision::logger(Logger::getLogger("goon.peripheral"));
	
// constructor
PeripheralVision::PeripheralVision (Retina& oRetina, Rois& oROIs) : mRetina(oRetina), mROIs(oROIs)
{
    LOG4CXX_INFO(logger, "goon " << GOON_VERSION << " - Peripheral vision");

    oUnitsDetection.setSizeReceptiveFields(8);          // this value produces receptive fields with double the area of their underlying objects.
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
void PeripheralVision::update ()
{
    int num_rois, merged_rois, eliminated_rois;
        
    LOG4CXX_TRACE(logger, "update - init");
    
    oUnitsDetection.prepareUnits();    

    std::vector<int>::iterator it_regID;
    std::vector<int>::iterator it_end = mRetina.getListFinalIDs().end();
        
    // walk the list of final retinal regions
    for (it_regID = mRetina.getListFinalIDs().begin(); it_regID != it_end; it_regID++)
    {
        Region& oRegion = mRetina.getRegion(*it_regID);        
        oUnitsDetection.respond2Region(oRegion);
    }    

    oUnitsDetection.updateUnits();
    
    // updates the detected ROIs
    computeROIs();

    oUnitsDetection.getNumbers(&merged_rois, &eliminated_rois);

    num_rois = mROIs.getNumROIs();
    LOG4CXX_DEBUG(logger, "rois = " << num_rois << ", merged = " << merged_rois << ", eliminated = " << eliminated_rois);

    storage[0] += mRetina.getNumFinalIDs();
    storage[1] += num_rois;
    storage[2] += merged_rois;
    storage[3] += eliminated_rois;
    counter++;
    
    LOG4CXX_TRACE(logger, "update - end");
}


// Rebuilds the list of active ROIs 
void PeripheralVision::computeROIs ()
{
    ROI oROI;      

    LOG4CXX_TRACE(logger, "compute ROIs");

    mROIs.clear();

    std::list<Unit>& list_units = oUnitsDetection.getListUnits();
    std::list<Unit>::iterator it_Unit;

    for (it_Unit = list_units.begin(); it_Unit != list_units.end(); it_Unit++)
    {                
        setROIFromUnit (oROI, *it_Unit);

        mROIs.addROI(oROI);
    }
}


// Transforms a Unit into a fully featured ROI (with motion info).
void PeripheralVision::setROIFromUnit (ROI &oROI, Unit &oUnit)
{
    LOG4CXX_TRACE(logger, "update ROI " << oUnit.getID());
    
    oROI.setID(oUnit.getID());
    oROI.setAge(oUnit.getAge());
    oROI.setStability(oUnit.getStability());
    
    oROI.updateBlob(oUnit);
    // update roi translation motion
    oROI.updateMotion(oUnit.getTransMove());
    
    LOG4CXX_TRACE(logger, "age = " << oROI.getAge() << ", stability = " << oROI.getStability());
}

void PeripheralVision::describeROIs()
{
    LOG4CXX_DEBUG(logger, "ROIs description ...");
    for (ROI& oROI: mROIs.getList()) 
    {
        LOG4CXX_DEBUG(logger, oROI.toString());
    } 
}


}

