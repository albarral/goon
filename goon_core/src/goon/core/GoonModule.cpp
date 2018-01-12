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
    pGoonBus = 0;
    pVisualData = 0;      
 }

void GoonModule::init(GoonBus& oGoonBus, VisualData& oVisualData)
{
    pGoonBus = &oGoonBus;
    pVisualData = &oVisualData;  
    benabled = true;    
    beat = 0;
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