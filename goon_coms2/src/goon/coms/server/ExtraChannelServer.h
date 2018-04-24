#ifndef __GOON_COMS_EXTRA_CHANNELSERVER_H
#define __GOON_COMS_EXTRA_CHANNELSERVER_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/talky/channel/ChannelServer.h"
#include "goon/coms/VisionConnector.h"

namespace goon
{
// Channel server implementation for vision extra topic.
class ExtraChannelServer : public tron2::ChannelServer, public VisionConnector
{       
private:
    bool bEndRequested;         // end of arm process requested
    
public:
    ExtraChannelServer();
    //~ExtraChannelServer();
    
    // process commands from received messages
    virtual void processCommands();
    
    bool getVisionEndRequested() {return bEndRequested;};
};

}
#endif
