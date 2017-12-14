#ifndef __GOON_PERIPHERAL_VISION_H
#define __GOON_PERIPHERAL_VISION_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/data/retina.h"
#include "goon/data/rois.h"
#include "goon/data/base/roi.h"
//#include "goon/peripheral/units_detection.h"
#include "goon/peripheral/RoisDetection.h"

namespace goon
{
class PeripheralVision
{
private:
    static log4cxx::LoggerPtr logger;
    Retina* pRetina;
    Rois* pROIs;
 //   UnitsDetection oUnitsDetection;
    RoisDetection oRoisDetection;
    int storage[4];
    int counter;
    int loop_time;      // time ellapsed from the last update (ms)

public:
    PeripheralVision();
    ~PeripheralVision();

    // Initializes the module 
    void init(Retina& oRetina, Rois& oROIs);

    void setParameters(int same_RGB, int similar_RGB);

    // This function implements the peripheral vision process.
    // It samples the retinal map to discover and track regions of interest in the visual scene.
    void update ();
       
    // logs a description of the computed ROIs
    void describeROIs();    
};

}  	

#endif
