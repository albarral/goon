/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/motion/Move.h"  

namespace goon 
{
// Constructor
Move::Move ()
{
    type = Move::eTYPE_IMAGE;   // default type is image move
    bstarted = false;
    millis = 0;
}

void Move::init()
{
    bstarted = true;
    t1 = std::chrono::steady_clock::now();
    millis = 0;
}

bool Move::update()
{
    if (bstarted)
    {
        std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
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
							 