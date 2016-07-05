/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>

#include "goon/utils/Module.h"


namespace goon
{    
// Constructor
Module::Module ()
{    
    state = prevState = Module::state_OFF;
    period = 0;
    bOffRequested = false;
}

void Module::on()
{
    std::lock_guard<std::mutex> locker(mutex);
    // launch a thread to execute the run method
    // skip if module is not OFF
    if (state == Module::state_OFF)
    {
      t = std::thread(&Module::run, this);              
    }           
}

void Module::off()
{        
    std::lock_guard<std::mutex> locker(mutex);
    bOffRequested = true;
}

void Module::wait()
{
    t.join();
}

void Module::setFrequency(float fps)
{
    std::lock_guard<std::mutex> locker(mutex);
    if (fps > 0.0)
        period = 1000000/fps;    // in microseconds
}

float Module::getFrequency()
{
    std::lock_guard<std::mutex> locker(mutex);
    if (period > 0)
        return (1000000/period);
    else
        return (0);        
}

void Module::run ()
{
    first();
    // run loop periodically until off is requested
    while (!isOffRequested())
    {
        loop();
        usleep(period);
    }
    
    // last action & OFF state
    bye();
    setState(Module::state_OFF);
}

bool Module::isOffRequested()
{
    std::lock_guard<std::mutex> locker(mutex);
    bool value = bOffRequested;
    // clear request
    bOffRequested = false;
    return value;        
}

int Module::getState()
{
    std::lock_guard<std::mutex> locker(mutex);
    return state;        
}

void Module::setState(int value)
{
    std::lock_guard<std::mutex> locker(mutex);
    prevState = state;
    state = value;    
}

int Module::getPrevState()
{
    std::lock_guard<std::mutex> locker(mutex);
    return prevState;        
}

// Usually not needed as this is done automatically by setState()
void Module::setPrevState(int value)
{
    std::lock_guard<std::mutex> locker(mutex);
    prevState = value;    
}

bool Module::isStateChanged()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state != prevState);
}

bool Module::isOff()
{
    std::lock_guard<std::mutex> locker(mutex);
    return (state == Module::state_OFF);
}

}

