#ifndef __GOON_VISION_MANAGER_H
#define __GOON_VISION_MANAGER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/vision/modules/Grab.h"
#include "goon/vision/modules/See.h"
#include "goon/vision/modules/Focus.h"
#include "goon/core/GoonBus.h"
#include "goon/core/VisualData.h"

namespace goon
{
// Manager of goon vision modules.
class VisionManager
{
private:
    static log4cxx::LoggerPtr logger;
    bool blaunched;     // indicates when the manager has been launched       
    // modules    
    Grab oGrab; // grab module (grabs images from camera)    
    See oSee;    // see module (retinal & peripheral vision)
    Focus oFocus;    // see module (retinal & peripheral vision)
    // logic
    int workingCamera;      // type of camera used
    
public:
    VisionManager();
    ~VisionManager();
                   
    bool launch(GoonBus& oGoonBus, VisualData& oVisualData);
    void end();
    
    void oneShot(GoonBus& oGoonBus, VisualData& oVisualData);
};

}
#endif
