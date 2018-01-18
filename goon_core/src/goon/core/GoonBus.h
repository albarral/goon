#ifndef __GOON_CORE_GOONBUS_H
#define __GOON_CORE_GOONBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>

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
        tuly::ControlT<cv::Vec3f> CO_FOCUS_SEARCH_VALUE;

        // SENSORS
        // Look
        tuly::SensorT<int> SO_LOOK_OBJECT;  // identified object
        tuly::SensorT<int> SO_LOOK_BEAT;  // Look module beat
        // Focus
        tuly::SensorT<int> SO_FOCUS_ROI;  // target focused ROI
        tuly::SensorT<int> SO_FOCUS_BEAT;  // Focus module beat
        // See
        tuly::SensorT<float> SO_SEE_FPS;  // frequency of See module
        tuly::SensorT<int> SO_SEE_BEAT;  // See module beat
        // Grab
        tuly::SensorT<int> SO_GRAB_BEAT;  // Grab module beat
        
    public:
        GoonBus();

        // CONTROLS        
        tuly::Control& getCO_FOCUS_SHIFT() {return CO_FOCUS_SHIFT;};
        tuly::ControlT<int>& getCO_FOCUS_MODE() {return CO_FOCUS_MODE;};
        tuly::ControlT<cv::Vec3f>& getCO_FOCUS_SEARCH_VALUE() {return CO_FOCUS_SEARCH_VALUE;};

        
        // SENSORS
        // Look
        tuly::SensorT<int>& getSO_LOOK_OBJECT() {return SO_LOOK_OBJECT;};  
        tuly::SensorT<int>& getSO_LOOK_BEAT() {return SO_LOOK_BEAT;};  
        // Focus
        tuly::SensorT<int>& getSO_FOCUS_ROI() {return SO_FOCUS_ROI;};  
        tuly::SensorT<int>& getSO_FOCUS_BEAT() {return SO_FOCUS_BEAT;};  
        // See
        tuly::SensorT<float>& getSO_SEE_FPS() {return SO_SEE_FPS;};
        tuly::SensorT<int>& getSO_SEE_BEAT() {return SO_SEE_BEAT;};  
        // Grab
        tuly::SensorT<int>& getSO_GRAB_BEAT() {return SO_GRAB_BEAT;};  
};

}
    
#endif
