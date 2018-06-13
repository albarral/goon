/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/coms/VisionConnector.h"

namespace goon
{
VisionConnector::VisionConnector()
{    
    pGoonBus = 0;
    bconnected = false;
}

void VisionConnector::connect2Bus(GoonBus& oGoonBus)
{
    pGoonBus = &oGoonBus;
    bconnected = true;
}

}