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
    MATCHING_HSV_SIMILARITY = 1.0;   
}


}
