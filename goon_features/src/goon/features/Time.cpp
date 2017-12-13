/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/Time.h"

namespace goon 
{
namespace features
{  
Time::Time()
{
    brunning = false;
    millis = 0;
}

void Time::start()
{
    t1 = std::chrono::steady_clock::now();
    millis = 0;
    brunning = true;
}

void Time::click()
{
    if (brunning)
    {
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        std::chrono::duration<int, std::milli> interval_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
        millis = interval_ms.count();        
        t1 = t2;
    }
}

void Time::read()
{
    if (brunning)
    {
        std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
        std::chrono::duration<int, std::milli> interval_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
        millis = interval_ms.count();        
    }
}

}
}