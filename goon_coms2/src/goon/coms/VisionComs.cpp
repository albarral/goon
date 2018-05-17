/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/coms/VisionComs.h"

namespace goon
{
log4cxx::LoggerPtr VisionComs::logger(log4cxx::Logger::getLogger("goon.coms"));

VisionComs::VisionComs() 
{
}

VisionComs::~VisionComs()
{    
}
     
 bool VisionComs::launch(GoonBus& oGoonBus)
{
    LOG4CXX_INFO(logger, "VisionComs: launch modules");
    float freq = 10.0; // TEMP oGoonConfig.getModulesFreq();
     
    // launch server module
    oVisionServer.init(oGoonBus);
    oVisionServer.setFrequency(freq);
    oVisionServer.on();
    
    return true;
}

bool VisionComs::end()
{
    LOG4CXX_INFO(logger, "VisionComs: end modules");

    // finish server module
    oVisionServer.off();
    oVisionServer.wait();      

    return true;
}

bool VisionComs::checkGoonEndRequested()
{
    return oVisionServer.getGoonEndRequested();
}

}		
