#ifndef __GOON_DATA_CORTEXCONFIG_H
#define __GOON_DATA_CORTEXCONFIG_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace goon
{
class CortexConfig
{
private:
    // binding
    float BINDING_OVERLAP_FRACTION;      
    // recognition        
    float MATCHING_HSV_SIMILARITY;                   // HSV distance used for color comparisons between a pixel and the region's color essence.

public:
    CortexConfig();
    //~CortexConfig();

    // binding
    float getBINDING_OVERLAP_FRACTION() {return BINDING_OVERLAP_FRACTION;}    
    // recognition        
    float getMATCHING_HSV_SIMILARITY() {return MATCHING_HSV_SIMILARITY;}
};
}

#endif
