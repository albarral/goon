/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/motion/Move.h"  

namespace goon 
{
namespace features
{    
// Constructor
Move::Move ()
{
    type = Move::eTYPE_IMAGE;   // default type is image move
    bstarted = false;
}

void Move::start(std::chrono::steady_clock::time_point& t)
{
    t1 = t;
    bstarted = true;
}

bool Move::update(std::chrono::steady_clock::time_point& t)
{
    if (bstarted)
    {
        std::chrono::duration<int, std::milli> interval_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t-t1);
        millis = interval_ms.count();        
        t1 = t;
        return true;
    }
    // if move not started, time interval can't be measured
    else
        return false;
}

}
}
							 