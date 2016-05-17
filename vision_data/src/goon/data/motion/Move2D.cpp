/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>

#include "goon/data/motion/Move2D.h"  

namespace goon 
{
// Constructor
Move2D::Move2D ()
{ 
    change[0] = 0;
    change[1] = 0;
    speed[0] = 0.0;
    speed[1] = 0.0;
}

void Move2D::init(int value[2])
{
    Move::init();
    this->value[0] = value[0];
    this->value[1] = value[1];
}

bool Move2D::update(int value[2])
{
    // if time interval measured ok, compute movement speed
    if (Move::update())
    {
        change[0] = value[0] - this->value[0];
        change[1] = value[1] - this->value[1];
        // update frequencies in the order of 1 to 100 Hz 
        // milliseconds can never be zero 
        if (millis == 0)
        {
            millis = 1;
            std::cout << "Error using goon::Move2D. Updated in less than 1 millisecond" << std::endl;
        }
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

std::string Move2D::toString()
{
    std::string desc = "Move2D: change=(" + std::to_string(change[0]) + ", " + std::to_string(change[1]) + 
            ") speed=(" + std::to_string(speed[0]) + ", " + std::to_string(speed[1]) + ") \n";

    return desc;
}
        
}
							 