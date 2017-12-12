/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "goon/look/GoonControl.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr GoonControl::logger(Logger::getLogger("goon.main"));

// Constructor
GoonControl::GoonControl ()
{    
}

// Destructor
GoonControl::~GoonControl ()
{
}

bool GoonControl::launch() 
{      
    bool bok = true;
    LOG4CXX_INFO(logger, "Launch goon control");
    
    // launch coms
    //bok = oGoonComs.launch(oGoonBus);        

    if (bok)
        // launch arm manager
        bok = oVisionManager.launch(oGoonBus, oVisualData, oCapture);

    if (bok)
    {
        // launch gui
        // monitoring module (shows output of the process)
        oGoonShow.init(oCapture, oVisualData, oGoonBus); 
        oGoonShow.setFrequency(30.0);
    }
    
    return bok;
}

bool GoonControl::end()
{
    // finish manager
    oVisionManager.end();

    // end coms
    //oGoonComs.end();

    // end gui
    if (oGoonShow.isOn())
    {
        oGoonShow.off();
        oGoonShow.wait();
    }

}

bool GoonControl::checkEndRequested()
{
    // return oGoonComs.checkAmyEndRequested();
    return false;
}

}



