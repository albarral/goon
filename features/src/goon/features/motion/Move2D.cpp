/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/motion/Move2D.h"  

namespace goon 
{
namespace features
{    
// Constructor
Move2D::Move2D ()
{ 
    change[0] = 0;
    change[1] = 0;
    speed[0] = 0.0;
    speed[1] = 0.0;
}

void Move2D::start(int value[2], std::chrono::steady_clock::time_point& t)
{
    Move::start(t);
    this->value[0] = value[0];
    this->value[1] = value[1];
}

bool Move2D::update(int value[2], std::chrono::steady_clock::time_point& t)
{
    // if time interval measured ok, compute movement speed
    if (Move::update(t))
    {
        change[0] = value[0] - this->value[0];
        change[1] = value[1] - this->value[1];
        // protect against time intervals under the millisecond (extremely rare)
        if (millis == 0)
            millis = 1;
        speed[0] = (float)change[0]/millis;
        speed[1] = (float)change[1]/millis;
        // and store position for next iteration 
        this->value[0] = value[0];
        this->value[1] = value[1];
        return true;
    }
    else
        return false;
}

}
}
							 