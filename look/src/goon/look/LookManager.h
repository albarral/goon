#ifndef __GOON_LOOK_MANAGER_H
#define __GOON_LOOK_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/look/bus/LookBus.h"
#include "goon/look/modules/Grab.h"
#include "goon/look/modules/See.h"
#include "goon/look/modules/LookMonitor.h"
#include "goon/data/capture.h"
#include "goon/data/visual_data.h"

namespace goon
{
// Manager of look modules.
class LookManager
{
private:
    static log4cxx::LoggerPtr logger;
    LookBus oLookBus;      // internal bus     
    // shared data
    VisualData oVisualData;    
    Capture oCapture;
    // modules    
    Grab oGrab; // grab module (grabs images from camera)    
    See oSee;    // see module (retinal & peripheral vision)
    LookMonitor oLookMonitor; // monitoring module (shows output of the process)
    // logic
    int workingCamera;      // type of camera used
    
public:
    LookManager();
    ~LookManager();
                   
    void startModules();
    void stopModules();
    
    void oneShot(int testCamera);
};

}
#endif
