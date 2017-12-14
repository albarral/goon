/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics  *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/coms/GoonComs.h"

namespace goon
{
log4cxx::LoggerPtr GoonComs::logger(log4cxx::Logger::getLogger("goon.coms"));

GoonComs::GoonComs() 
{
}

GoonComs::~GoonComs()
{    
}
     
 bool GoonComs::launch(GoonBus& oGoonBus)
{
    LOG4CXX_INFO(logger, "GoonComs: launch modules");
    float freq = 10.0; // TEMP oGoonConfig.getModulesFreq();
     
    // launch listener module
    oGoonListener.init(oGoonBus);
    oGoonListener.setFrequency(freq);
    oGoonListener.on();
    
    return true;
}

bool GoonComs::end()
{
    LOG4CXX_INFO(logger, "GoonComs: end modules");

    // finish listener module
    oGoonListener.off();
    oGoonListener.wait();      
    
    return true;
}

bool GoonComs::checkGoonEndRequested()
{
    // checks for received special actions
    oGoonListener.checkSpecialActions();
    
    return oGoonListener.getGoonEndRequested();
}

}		
