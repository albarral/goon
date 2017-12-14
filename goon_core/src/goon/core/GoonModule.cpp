/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/core/GoonModule.h"

namespace goon
{
// Constructor 
GoonModule::GoonModule()
{    
    modName = "GoonModule";
    benabled = false;
    beat = 0;
    pGoonBus = 0;
    pVisualData = 0;      
 }

void GoonModule::init(GoonBus& oGoonBus, VisualData& oVisualData)
{
    pGoonBus = &oGoonBus;
    pVisualData = &oVisualData;  
    benabled = true;    
    showInitialized();
}

void GoonModule::newBeat()
{
    // produce new beat
    beat++;
    if (beat == 1000)
        beat = 0;
}

}