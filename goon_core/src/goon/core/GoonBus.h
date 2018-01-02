#ifndef __GOON_CORE_GOONBUS_H
#define __GOON_CORE_GOONBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "tuly/control/brooks/control.h"
#include "tuly/control/brooks/controlT.h"
#include "tuly/control/brooks/sensorT.h"

namespace goon 
{
// Set of bus connections for look modules
class GoonBus
{
    private:        
        // CONTROLS
        // Focus
        tuly::Control CO_FOCUS_SHIFT;
        tuly::ControlT<int> CO_FOCUS_MODE;
        tuly::ControlT<float> CO_FOCUS_SEARCH_V0;
        tuly::ControlT<float> CO_FOCUS_SEARCH_V1;
        tuly::ControlT<float> CO_FOCUS_SEARCH_V2;

        // SENSORS
        // Focus
        tuly::SensorT<int> SO_FOCUS_BEAT;  // Focus module beat
        tuly::SensorT<int> SO_FOCUS_ROI;  // target focused ROI
        // See
        tuly::SensorT<int> SO_SEE_BEAT;  // See module beat
        tuly::SensorT<float> SO_SEE_FPS;  // frequency of See module
        // Grab
        tuly::SensorT<int> SO_GRAB_BEAT;  // Grab module beat
        
    public:
        GoonBus();

        // CONTROLS        
        tuly::Control& getCO_FOCUS_SHIFT() {return CO_FOCUS_SHIFT;};
        tuly::ControlT<int>& getCO_FOCUS_MODE() {return CO_FOCUS_MODE;};
        tuly::ControlT<float>& getCO_FOCUS_SEARCH_V0() {return CO_FOCUS_SEARCH_V0;};
        tuly::ControlT<float>& getCO_FOCUS_SEARCH_V1() {return CO_FOCUS_SEARCH_V1;};
        tuly::ControlT<float>& getCO_FOCUS_SEARCH_V2() {return CO_FOCUS_SEARCH_V2;};

        
        // SENSORS
        // Focus
        tuly::SensorT<int>& getSO_FOCUS_BEAT() {return SO_FOCUS_BEAT;};  
        tuly::SensorT<int>& getSO_FOCUS_ROI() {return SO_FOCUS_ROI;};  
        // See
        tuly::SensorT<int>& getSO_SEE_BEAT() {return SO_SEE_BEAT;};  
        tuly::SensorT<float>& getSO_SEE_FPS() {return SO_SEE_FPS;};
        // Grab
        tuly::SensorT<int>& getSO_GRAB_BEAT() {return SO_GRAB_BEAT;};  
};

}
    
#endif
