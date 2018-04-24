/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/coms/server/FocusChannelServer.h"
#include "tron2/talky/vision/FocusTalker.h"
#include "tron2/robot/RobotNodes.h"
#include "tron2/robot/topics/VisionTopics.h"

using namespace log4cxx;

namespace goon
{
FocusChannelServer::FocusChannelServer() 
{    
    tron2::ChannelServer::tune4NodeAndTopic(tron2::RobotNodes::eNODE_VISION, tron2::VisionTopics::eVISION_FOCUS);
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
            if (pTalker->interpretMessage(message, code, value))
            {
                switch (code)
                {
                    case tron2::FocusTalker::eFOCUS_SHIFT:
                        LOG4CXX_INFO(logger, "> shift focus ");                        
                        pGoonBus->getCO_FOCUS_SHIFT().request();
                        break;

                    case tron2::FocusTalker::eFOCUS_MODE:
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

