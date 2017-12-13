/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/show/GoonShow.h"

namespace goon
{  
log4cxx::LoggerPtr GoonShow::logger(log4cxx::Logger::getLogger("goon.show"));

GoonShow::GoonShow() 
{
    blaunched = false;    
}

GoonShow::~GoonShow() 
{
}

bool GoonShow::launch(GoonBus& oGoonBus, VisualData& oVisualData, Capture& oCapture)
{
    // launch it if not launched yet
    if (!blaunched)
    {
        LOG4CXX_INFO(logger, "Launching GoonShow");
        
        //float freq = pGoonConfig->getModulesFreq();
        float freq = 20.0; // TEMP to get from config

        oShowRetina.init(oCapture, oVisualData, oGoonBus);
        oShowRetina.setFrequency(freq);    

        // launch modules
        oShowRetina.on();    
        
        blaunched = true;    
    }
    // report problems
    else
        LOG4CXX_ERROR(logger, "Can't launch GoonShow: already launched!");        
    
    return blaunched;
};

void GoonShow::end()
{
    LOG4CXX_INFO(logger, "stopping GoonShow ..."); 

    if (oShowRetina.isOn())
    {    
        oShowRetina.off();
        oShowRetina.wait();
    }

    LOG4CXX_INFO(logger, "GoonShow finished");  
}

// just one loop exectution (for testing)
void GoonShow::oneShot(GoonBus& oGoonBus, VisualData& oVisualData, Capture& oCapture)
{
    LOG4CXX_INFO(logger, "GoonShow: one shot ..."); 
    oShowRetina.init(oCapture, oVisualData, oGoonBus);   
    oShowRetina.oneShot();
}

}
