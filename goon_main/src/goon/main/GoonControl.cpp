/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "goon/main/GoonControl.h"

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
    bok = oGoonComs.launch(oGoonBus);        

    if (bok)
        // launch vision manager
        bok = oVisionManager.launch(oGoonBus, oVisualData);

    if (bok)
        // launch gui
        bok = oGoonShow.launch(oGoonBus, oVisualData);
    
    return bok;
}

bool GoonControl::end()
{
    // finish manager
    oVisionManager.end();

    // end coms
    oGoonComs.end();

    // end gui
    oGoonShow.end();
}

void GoonControl::oneShot()
{
    oVisionManager.oneShot(oGoonBus, oVisualData);
    oGoonShow.oneShot(oGoonBus, oVisualData);    
}

bool GoonControl::checkEndRequested()
{
    return oGoonComs.checkGoonEndRequested();
}

}



