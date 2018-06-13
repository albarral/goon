/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "goon/coms/modules/VisionServer.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr VisionServer::logger(Logger::getLogger("goon.coms"));

// Constructor 
VisionServer::VisionServer()
{    
    modName = "VisionServer";
    benabled = false;
 }

void VisionServer::init(GoonBus& oGoonBus)
{
    // prepare communication servers
    oFocusChannelServer.connect2Bus(oGoonBus);    
    oExtraChannelServer.connect2Bus(oGoonBus);    
    
    // if servers enabled
    if (oFocusChannelServer.isTuned() && 
        oExtraChannelServer.isTuned())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, channel servers not tuned!");                        
}

void VisionServer::first()
{    
    log4cxx::NDC::push(modName);   	
}

void VisionServer::loop()
{
    // check focus channel
    checkChannelServer(oFocusChannelServer);        
    // check extra channel
    checkChannelServer(oExtraChannelServer);        
}

bool VisionServer::checkChannelServer(tron2::ChannelServer& oChannelServer)
{    
    // receive messages from the given channel
    if (oChannelServer.senseChannel())
    {
        // and process them
        oChannelServer.processCommands();
        return true;
    }
    // if no messages could be read
    else
        return false;
}

bool VisionServer::getGoonEndRequested()
{
    return oExtraChannelServer.getVisionEndRequested();
}

}