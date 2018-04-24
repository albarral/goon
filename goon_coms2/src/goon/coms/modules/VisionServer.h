#ifndef __GOON_COMS_VISIONSERVER_H
#define __GOON_COMS_VISIONSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "goon/coms/server/FocusChannelServer.h"
#include "goon/coms/server/ExtraChannelServer.h"
#include "tron2/talky/channel/ChannelServer.h"
#include "goon/core/GoonBus.h"
#include "tron/control/module3.h"

namespace goon
{
// This module serves external control request for vision control. 
// It uses a dedicated channel server for each communications channel (one for each vision topic).
class VisionServer : public tron::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    FocusChannelServer oFocusChannelServer;     // communications server for focus channel
    ExtraChannelServer oExtraChannelServer;    // communications server for extra channel

public:
    VisionServer();
    //~VisionServer();

    void init(GoonBus& oGoonBus);       
    bool isEnabled() {return benabled;};
        
    bool getGoonEndRequested();        

private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given channel server for received messages and process them
    bool checkChannelServer(tron2::ChannelServer& oChannelServer);
};
}		
#endif
