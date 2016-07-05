/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/utils/Click.h"

namespace goon 
{
namespace utils
{  
Click::Click()
{
    bstarted = false;
    millis = micros = 0;
}

void Click::start()
{
    t1 = std::chrono::steady_clock::now();
    bstarted = true;
}

void Click::read()
{
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    if (bstarted)
    {
        std::chrono::duration<int, std::milli> interval_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1);
        std::chrono::duration<int, std::micro> interval_us = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1);
        millis = interval_ms.count();        
        micros = interval_us.count();        
    }
}

}
}