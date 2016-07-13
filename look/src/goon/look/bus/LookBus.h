#ifndef __GOON_LOOK_BUS_H
#define __GOON_LOOK_BUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/utils/brooks/sensorT.h"

namespace goon 
{
// Set of bus connections for look modules
class LookBus
{
    private:        
        // SENSORS (sender modules)        
        // See
        brooks::SensorT<int> SO_SEE_BEAT;  // beat of See module
        brooks::SensorT<float> SO_SEE_FPS;  // frequency of See module
        
    public:
        LookBus();

        // sensors
        brooks::SensorT<int>& getSO_SEE_BEAT() {return SO_SEE_BEAT;};  
        brooks::SensorT<float>& getSO_SEE_FPS() {return SO_SEE_FPS;};
};

}
    
#endif
