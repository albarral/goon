#ifndef __GOON_CORE_GOONBUS_H
#define __GOON_CORE_GOONBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>

#include "tron/control/brooks/control.h"
#include "tron/control/brooks/controlT.h"
#include "tron/control/brooks/sensor.h"
#include "tron/control/brooks/sensorT.h"

namespace goon 
{
// Set of bus connections for look modules
class GoonBus
{
    private:        
        // CONTROLS
        // Focus
        tron::Control CO_FOCUS_SHIFT;
        tron::ControlT<int> CO_FOCUS_MODE;
        tron::ControlT<cv::Vec3f> CO_FOCUS_SEARCH_VALUE;

        // SENSORS
        // Look
        tron::SensorT<int> SO_LOOK_BEAT;  // Look module beat
        tron::SensorT<int> SO_LOOK_OBJECT;  // identified object
        // Focus
        tron::SensorT<int> SO_FOCUS_BEAT;  // Focus module beat
        tron::Sensor SO_FOCUS_FOCUSED;  // target focused flag
        tron::SensorT<int> SO_FOCUS_ROI;  // target focused ROI
        // See
        tron::SensorT<int> SO_SEE_BEAT;  // See module beat
        tron::SensorT<float> SO_SEE_FPS;  // frequency of See module
        // Grab
        tron::SensorT<int> SO_GRAB_BEAT;  // Grab module beat
        
    public:
        GoonBus();

        // CONTROLS        
        tron::Control& getCO_FOCUS_SHIFT() {return CO_FOCUS_SHIFT;};
        tron::ControlT<int>& getCO_FOCUS_MODE() {return CO_FOCUS_MODE;};
        tron::ControlT<cv::Vec3f>& getCO_FOCUS_SEARCH_VALUE() {return CO_FOCUS_SEARCH_VALUE;};

        
        // SENSORS
        // Look
        tron::SensorT<int>& getSO_LOOK_BEAT() {return SO_LOOK_BEAT;};  
        tron::SensorT<int>& getSO_LOOK_OBJECT() {return SO_LOOK_OBJECT;};  
        // Focus
        tron::SensorT<int>& getSO_FOCUS_BEAT() {return SO_FOCUS_BEAT;};  
        tron::Sensor& getSO_FOCUS_FOCUSED() {return SO_FOCUS_FOCUSED;};  
        tron::SensorT<int>& getSO_FOCUS_ROI() {return SO_FOCUS_ROI;};  
        // See
        tron::SensorT<int>& getSO_SEE_BEAT() {return SO_SEE_BEAT;};  
        tron::SensorT<float>& getSO_SEE_FPS() {return SO_SEE_FPS;};
        // Grab
        tron::SensorT<int>& getSO_GRAB_BEAT() {return SO_GRAB_BEAT;};  
};

}
    
#endif
