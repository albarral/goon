/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/coms/server/FocusChannelServer.h"
#include "tron2/robot/RobotNetwork.h"
#include "tron2/robot/RobotSystem.h"
#include "tron2/robot/vision/VisionNode.h"
#include "tron2/robot/vision/FocusTopic.h"

using namespace log4cxx;

namespace goon
{
FocusChannelServer::FocusChannelServer() 
{    
    tron2::ChannelServer::connect2Channel(tron2::RobotSystem::eNODE_VISION, tron2::RobotNetwork::eVISION_FOCUS_CHANNEL, tron2::VisionNode::eVISION_FOCUS);
}

//FocusChannelServer::~FocusChannelServer()
//{    
//}

void FocusChannelServer::processCommands()
{    
    int code;
    float value;
    
    if (!bconnected)
    {
        LOG4CXX_ERROR(logger, "FocusChannelServer: can't process data, not connected to vision bus");
        return;        
    }
    
    if (btuned)    
    {        
        // process received messages
        for (std::string message : listMessages)
        {
            LOG4CXX_TRACE(logger, "FocusChannelServer: check msg " << message);
            // if message interpreted, call proper bus action
            if (oTalker.interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::FocusTopic::eFOCUS_SHIFT:
                        LOG4CXX_INFO(logger, "> shift focus ");                        
                        pGoonBus->getCO_FOCUS_SHIFT().request();
                        break;

                    case tron2::FocusTopic::eFOCUS_MODE:
                        LOG4CXX_INFO(logger, "> focus mode " << value);                        
                        pGoonBus->getCO_FOCUS_MODE().request((int)value);
                        break;

                    default:
                        LOG4CXX_WARN(logger, "FocusChannelServer: can't process command, untreated concept " << code);                                   
                }    
            }
            else
            {
                LOG4CXX_WARN(logger, "FocusChannelServer: joint command not interpreted");
            }
        }
    }
    else
    {
        LOG4CXX_ERROR(logger, "FocusChannelServer: can't process data, communicator not tuned");
        return;
    }        
}

}

