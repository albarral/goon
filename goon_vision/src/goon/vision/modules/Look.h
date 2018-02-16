#ifndef __GOON_VISION_LOOK_H
#define __GOON_VISION_LOOK_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>
#include <opencv2/core/core.hpp>

#include "goon/core/GoonModule.h"
#include "goon/cortex/CortexVision.h"
#include "goon/data/base/roi.h"
#include "goon/data/cortex/Object.h"
#include "tuly/control/SensorLed.h"

namespace goon
{    
// Module in charge of binding and identifying objects.
class Look : public GoonModule
{
public:
    // states of Look module
    enum eState
    {
        eSTATE_WAIT,
        //eSTATE_NEW_FOCUS,
        eSTATE_IDENTIFY
    };

private:
    static log4cxx::LoggerPtr logger;
    // logic
    Object oObject;    // looked object    
    CortexVision oCortexVision;
    int focusedROI;      // ID of focused ROI
    int lookedObject;   // ID of identified object
    tuly::SensorLed oFocusBeatLed;   // sensor led for Focus module's beat

public:
    Look();
    //~Look();
        
    // just one loop execution (for testing)
    void oneShot();       

private:
    // show module initialization in logs
    virtual void showInitialized();    
    // first action after thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    // last action before thread ends
    virtual void bye();
    
    void senseBus();
    void writeBus();
    void showState();

    // clear object
    void clearObject();
    // do object binding
    void formObject();
    // do object identification
    void identifyObject();

    //bool changeFocus();

    // waits first beat from focus module
    void wait4FocusBeat();
};

}
#endif
