#ifndef __GOON_CORTEX_CONFIGCORTEX_H
#define __GOON_CORTEX_CONFIGCORTEX_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace goon
{
class ConfigCortex
{
private:
    // binding
    float BINDING_OVERLAP_FRACTION;      


public:
    ConfigCortex();
    //~ConfigCortex();

    // binding
    float getBINDING_OVERLAP_FRACTION() {return BINDING_OVERLAP_FRACTION;}    
};
}

#endif
