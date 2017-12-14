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
        // SENSORS 
        // See
        tuly::SensorT<int> SO_SEE_BEAT;  // See module's beat
        tuly::SensorT<float> SO_SEE_FPS;  // frequency of See module
        // Grab
        tuly::SensorT<int> SO_GRAB_BEAT;  // Grab module's beat
        
    public:
        GoonBus();

        // sensors
        // See
        tuly::SensorT<int>& getSO_SEE_BEAT() {return SO_SEE_BEAT;};  
        tuly::SensorT<float>& getSO_SEE_FPS() {return SO_SEE_FPS;};
        // Grab
        tuly::SensorT<int>& getSO_GRAB_BEAT() {return SO_GRAB_BEAT;};  
};

}
    
#endif
