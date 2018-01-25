/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "goon/coms/modules/GoonListener.h"
#include "talky/Topics.h"
#include "talky/topics/VisionTopic.h"
#include "tuly/utils/IntegerQueue.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr GoonListener::logger(Logger::getLogger("goon.coms"));

// Constructor 
GoonListener::GoonListener()
{    
    modName = "GoonListener";
    benabled = false;
 }

void GoonListener::init(GoonBus& oGoonBus)
{
    int topic = talky::Topics::eTOPIC_VISION;
    // prepare communication servers
    oNetyServerFocus.init(topic, talky::VisionTopic::eCAT_VISION_FOCUS);    
    oNetyServerExtra.init(topic, talky::VisionTopic::eCAT_VISION_EXTRA);    
    
    oCIGoonControl.connect2Arm(&oGoonBus);
    
    // if servers enabled
    if (oNetyServerFocus.isConnected() &&
            oNetyServerExtra.isConnected())
    {
        benabled = true;
        LOG4CXX_INFO(logger, modName + " initialized");                                
    }
    else
        LOG4CXX_ERROR(logger, modName + ": failed initialization, server nodes not connected!");                        
}

void GoonListener::first()
{    
    log4cxx::NDC::push(modName);   	
}

void GoonListener::loop()
{
    // listen to focus messages
    checkServer(oNetyServerFocus);
    // listen to extra messages
    checkServer(oNetyServerExtra);
}

void GoonListener::checkServer(nety::NetNodeServer& oNetyServer)
{
    talky::Command oCommand;

    // get received messages
    oNetyServer.absorb();
    // process them to commands
    oNetyServer.process();
    // consume commands queue
    while (oNetyServer.hasCommands())
    {                    
        // process each command to a proper bus action
        if (oNetyServer.fetchCommand(oCommand))
        {
            LOG4CXX_INFO(logger, modName + ": cmd received - " + oCommand.toString());        
            oCIGoonControl.processCommand(oCommand);
        }
    }                
}

bool GoonListener::checkSpecialActions()
{
    // clear all flags
    brequestedGoonEnd = false;

    tuly::IntegerQueue& oQueue = oCIGoonControl.getQueueSpecialActions();
    int numActions = oQueue.getSize();
    int action; 
    // consume queue of special actions
    while (oQueue.isFilled())
    {
         oQueue.fetch(action);
         // set flags proper to requested actions    
         switch (action)
         {
             case ComsInGoonControl::eACTION_GOON_END:
                 brequestedGoonEnd = true;
                 break;
         }
    }
        
    return (numActions > 0);    
}

}