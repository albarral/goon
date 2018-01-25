/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/coms/in/ComsInGoonControl.h"
#include "talky/topics/VisionTopic.h"

namespace goon
{
log4cxx::LoggerPtr ComsInGoonControl::logger(log4cxx::Logger::getLogger("goon.coms"));

ComsInGoonControl::ComsInGoonControl()
{    
    pGoonBus = 0;
}

void ComsInGoonControl::connect2Arm(GoonBus* pGoonBus)
{
    this->pGoonBus = pGoonBus;
}


bool ComsInGoonControl::processCommand(talky::Command& oCommand)
{
    bool bret = true;

    // skip if no interface connection
    if (pGoonBus == 0)
    {
        LOG4CXX_ERROR(logger, "ComsInGoonControl: can't process command, no bus connection");           
        return false;
    }

    switch (oCommand.getCategory())
    {
        case talky::VisionTopic::eCAT_VISION_FOCUS:
            bret = processFocusCommand(oCommand);
            break;

        case talky::VisionTopic::eCAT_VISION_EXTRA:
            bret = processExtraCommand(oCommand);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInGoonControl: can't process command, untreated category " << oCommand.getCategory());                        
    }                
    return bret;
}

bool ComsInGoonControl::processFocusCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {            
        case talky::VisionTopic::eFOCUS_SHIFT:
            LOG4CXX_INFO(logger, "> focus shift");  
            pGoonBus->getCO_FOCUS_SHIFT().request();
            break;

        case talky::VisionTopic::eFOCUS_MODE:
            LOG4CXX_INFO(logger, "> focus mode" << (int)quantity);  
            pGoonBus->getCO_FOCUS_MODE().request((int)quantity);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInGoonControl: can't process command, untreated extra concept " << oCommand.getConcept());           
    }    
    return bret;
}

bool ComsInGoonControl::processExtraCommand(talky::Command& oCommand)
{
    bool bret = true;
    float quantity = oCommand.getQuantity();
    
    switch (oCommand.getConcept())
    {            
        case talky::VisionTopic::eEXTRA_VISION_END:
            LOG4CXX_INFO(logger, "> end goon");  
            oQueueSpecialActions.add(ComsInGoonControl::eACTION_GOON_END);
            break;

        default:
            bret = false;
            LOG4CXX_WARN(logger, "ComsInGoonControl: can't process command, untreated extra concept " << oCommand.getConcept());           
    }    
    return bret;
}


void ComsInGoonControl::toDoCommand(float value)
{
    // nothing done
    // dummy method for to do commands
    LOG4CXX_INFO(logger, "> to do");                        
}

}