/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/config/CortexConfig.h"
		
namespace goon
{
// constructor
CortexConfig::CortexConfig()
{
    // binding
    BINDING_OVERLAP_FRACTION = 0.50;
    // recognition        
    EVIDENCE_SENSITIVITY = 0.8;   
    MATCHING_SENSITIVITY = 0.5;   
    COMPARE_COLOR_TOLERANCE = 30.0;   
    COMPARE_ANGLE_TOLERANCE = 45.0;   
    COMPARE_REQUIRED_SIMILARITY = 3.0;   
}


}
