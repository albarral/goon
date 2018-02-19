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
    float EVIDENCE_SENSITIVITY;                  // sensitivity of evidence process
    float MATCHING_SENSITIVITY;                  // sensitivity of matching process
    float COMPARE_COLOR_TOLERANCE;        // tolerance for color similarity (degrees)
    float COMPARE_ANGLE_TOLERANCE;         // tolerance for for orientation similarity (degrees)
    float COMPARE_REQUIRED_SIMILARITY;      // required similarity to consider a region correspondence

public:
    CortexConfig();
    //~CortexConfig();

    // binding
    float getBINDING_OVERLAP_FRACTION() {return BINDING_OVERLAP_FRACTION;}    
    // recognition        
    float getEVIDENCE_SENSITIVITY () {return EVIDENCE_SENSITIVITY;}
    float getMATCHING_SENSITIVITY() {return MATCHING_SENSITIVITY;}
    float getCOMPARE_COLOR_TOLERANCE() {return COMPARE_COLOR_TOLERANCE;}
    float getCOMPARE_ANGLE_TOLERANCE() {return COMPARE_ANGLE_TOLERANCE;}
    float getCOMPARE_REQUIRED_SIMILARITY() {return COMPARE_REQUIRED_SIMILARITY;}
};
}

#endif
