#ifndef __GOON_COMS_FOCUS_CHANNELSERVER_H
#define __GOON_COMS_FOCUS_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/talky/channel/ChannelServer.h"
#include "goon/coms/VisionConnector.h"

namespace goon
{
// Channel server implementation for vision focus topic.
class FocusChannelServer : public tron2::ChannelServer, public VisionConnector
{            
public:
    FocusChannelServer();
    //~FocusChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
};

}
#endif
