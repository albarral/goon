#ifndef __GOON_CORE_GOONBUS_H
#define __GOON_CORE_GOONBUS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>

#include "tron/control/brooks/control.h"
#include "tron/control/brooks/control2.h"
#include "tron/control/brooks/controlT.h"
#include "tron/control/brooks/sensor.h"
#include "tron/control/brooks/sensor2.h"
#include "tron/control/brooks/sensor3.h"

namespace goon 
{
// Set of bus connections for look modules
class GoonBus
{
    private:        
        // CONTROLS
        // Focus
        tron::Control CO_FOCUS_SHIFT;
        tron::Control2 CO_FOCUS_MODE;
        tron::ControlT<cv::Vec3f> CO_FOCUS_SEARCH_VALUE;

        // SENSORS
        // Look
        tron::Sensor2 SO_LOOK_BEAT;  // Look module beat
        tron::Sensor2 SO_LOOK_OBJECT;  // identified object
        // Focus
        tron::Sensor2 SO_FOCUS_BEAT;  // Focus module beat
        tron::Sensor SO_FOCUS_FOCUSED;  // target focused flag
        tron::Sensor2 SO_FOCUS_ROI;  // target focused ROI
        // See
        tron::Sensor2 SO_SEE_BEAT;  // See module beat
        tron::Sensor3 SO_SEE_FPS;  // frequency of See module
        // Grab
        tron::Sensor2 SO_GRAB_BEAT;  // Grab module beat
        
    public:
        GoonBus();

        // CONTROLS        
        tron::Control& getCO_FOCUS_SHIFT() {return CO_FOCUS_SHIFT;};
        tron::Control2& getCO_FOCUS_MODE() {return CO_FOCUS_MODE;};
        tron::ControlT<cv::Vec3f>& getCO_FOCUS_SEARCH_VALUE() {return CO_FOCUS_SEARCH_VALUE;};

        
        // SENSORS
        // Look
        tron::Sensor2& getSO_LOOK_BEAT() {return SO_LOOK_BEAT;};  
        tron::Sensor2& getSO_LOOK_OBJECT() {return SO_LOOK_OBJECT;};  
        // Focus
        tron::Sensor2& getSO_FOCUS_BEAT() {return SO_FOCUS_BEAT;};  
        tron::Sensor& getSO_FOCUS_FOCUSED() {return SO_FOCUS_FOCUSED;};  
        tron::Sensor2& getSO_FOCUS_ROI() {return SO_FOCUS_ROI;};  
        // See
        tron::Sensor2& getSO_SEE_BEAT() {return SO_SEE_BEAT;};  
        tron::Sensor3& getSO_SEE_FPS() {return SO_SEE_FPS;};
        // Grab
        tron::Sensor2& getSO_GRAB_BEAT() {return SO_GRAB_BEAT;};  
};

}
    
#endif
