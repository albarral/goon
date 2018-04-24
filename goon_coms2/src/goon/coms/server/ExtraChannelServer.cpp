/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/coms/server/ExtraChannelServer.h"
#include "tron2/talky/BasicTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/VisionTopics.h"

using namespace log4cxx;

namespace goon
{
ExtraChannelServer::ExtraChannelServer()
{    
    bEndRequested = false;
    tron2::ChannelServer::tune4NodeAndTopic(tron2::RobotNodes::eNODE_VISION, tron2::VisionTopics::eVISION_EXTRA);
}

//ExtraChannelServer::~ExtraChannelServer()
//{    
//}

void ExtraChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "ExtraChannelServer: can't process data, not connected to vision bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "ExtraChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::BasicTalker::eBASIC_CONTROL_END:
                        LOG4CXX_INFO(logger, "> end vision");  
                        bEndRequested = true;
                        break;

                    default:
                        LOG4CXX_WARN(logger, "ExtraChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "ExtraChannelServer: extra command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "ExtraChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}
