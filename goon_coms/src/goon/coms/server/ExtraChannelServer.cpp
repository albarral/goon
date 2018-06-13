/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/coms/server/ExtraChannelServer.h"
#include "goon/interface/VisionNode.h"
#include "tron2/robot/common/ExtraTopic.h"
#include "tron2/robot/RobotSystem.h"

using namespace log4cxx;

namespace goon
{
ExtraChannelServer::ExtraChannelServer()
{    
    bEndRequested = false;
    int channel = VisionNode::eVISION_EXTRA_CHANNEL;
    tron2::ChannelServer::connect2Channel(tron2::RobotSystem::eNODE_VISION, channel, VisionNode::getTopic4Channel(channel));
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
            if (oTalker.interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::ExtraTopic::eEXTRA_STOP:
                        LOG4CXX_INFO(logger, "> vision stop ... TO DO");                        
                        break;

                    case tron2::ExtraTopic::eEXTRA_END:
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
