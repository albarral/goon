#ifndef __GOON_FEATURES_TIME_H
#define __GOON_FEATURES_TIME_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <chrono>

namespace goon 
{
namespace features
{  
// Utility class for computing time intervals (in milliseconds).
// Start measuring with start()
// Measure interval with read(), time keeps running
// Measure and restart interval with click()
// Get interval size with getMillis().    
class Time
{
private:
    bool brunning; // time is running (t1 informed)
    std::chrono::steady_clock::time_point t1;   // starting point of the time interval
    int millis;     // measured interval (milliseconds)

public:

    Time();
    // starts the time measure (initializes t1)
    void start();
    // measures the elapsed time & restarts the time measure (updates t1)
    void click();
    // measures the elapsed time, but keeps the time running (does not update t1))
    void read();
    // returns computed elapsed time in milliseconds
    int getMillis() {return millis;};
    
};

}
}
#endif
