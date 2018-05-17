#ifndef __GOON_COMS_VISIONCONNECTOR_H
#define __GOON_COMS_VISIONCONNECTOR_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/core/GoonBus.h"

namespace goon
{
// Base class used to connect to vision bus.
class VisionConnector 
{    
protected:
    GoonBus* pGoonBus;      // access to vision bus
    bool bconnected;
    
public:
    VisionConnector();
    //~VisionConnector();
    
    virtual void connect2Bus(GoonBus& oGoonBus);
    bool isConnected() {return bconnected;};
};
}
#endif
