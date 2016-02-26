#ifndef __GOON_UTILS_CLICK_H
#define __GOON_UTILS_CLICK_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <chrono>

namespace goon 
{
namespace utils
{  
// Utility class for computing time intervals.
// Set the time start point with start()
// Set the time end point & compute the ellapsed time with read()
// Get the measured time with getMillis() or getMicros().    
class Click
{
private:
    std::chrono::steady_clock::time_point t1;
    int millis;     // last measure in milliseconds
    int micros;   // last measure in microseconds
    bool bstarted; // chrono has been started

public:

    Click();
    // stores initial time point t1
    void start();
    // measures the ellapsed time since the last start (t - t1), and stores it in millis & micros
    void read();    
    // returns the computed ellapsed time in milliseconds
    int getMillis() {return millis;};
    // returns the computed ellapsed time in microseconds
    int getMicros() {return micros;};
    
};

}
}
#endif
