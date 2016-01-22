/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include "goon/utils/trigger.h"

namespace goon
{
// constructor
Trigger::Trigger ()
{
    // by default the trigger responds to value changes of 10% (limited to a minimum of 100 units)  
    CHANGE_FACTOR = 0.1;
    MIN_CHANGE = 100;   
}

// destructor
Trigger::~Trigger()
{
}


void Trigger::setParams(float change_factor, int min_change)
{
    CHANGE_FACTOR = change_factor;
    MIN_CHANGE = min_change;   
}


void Trigger::reset()
{
    trigger_value = MIN_CHANGE;            
}


void Trigger::update(int present_value)
{    
    // set condition for next update
    int change = present_value * CHANGE_FACTOR;
    if (change > MIN_CHANGE)
        trigger_value = present_value + change;
    else 
        trigger_value = present_value + MIN_CHANGE;            
}

}
