#ifndef __GOON_CORE_GOONBUS_H
#define __GOON_CORE_GOONBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tuly/control/brooks/sensorT.h"

namespace goon 
{
// Set of bus connections for look modules
class GoonBus
{
    private:        
        // SENSORS (sender modules)        
        // See
        tuly::SensorT<int> SO_SEE_BEAT;  // beat of See module
        tuly::SensorT<float> SO_SEE_FPS;  // frequency of See module
        
    public:
        GoonBus();

        // sensors
        tuly::SensorT<int>& getSO_SEE_BEAT() {return SO_SEE_BEAT;};  
        tuly::SensorT<float>& getSO_SEE_FPS() {return SO_SEE_FPS;};
};

}
    
#endif
