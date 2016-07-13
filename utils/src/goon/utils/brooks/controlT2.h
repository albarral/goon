#ifndef _GOON_BROOKS_CONTROLT2_H
#define _GOON_BROOKS_CONTROLT2_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

namespace goon 
{
namespace brooks
{    
// This class implements a Brooks control command. It provides supression mechanism by using request priorities.
// The control has a value, an activation flag and an associated priority.
// Initially the control is deactivated and has zero priority.
// On control requests, the control is activated with the new value and priority. But only if the requested priority is higher or equal than the active one.
// On control checks, the value is returned and the priority and activation flag are reset.
// Thread safe
template <typename T>
class ControlT2
{
    private:
        std::mutex mutex;
        bool brequested;           // control requested flag        
        T value;                        // requested value        
        int reqPriority;               // requested priority 

    public:
        ControlT2();
        //~ControlT2();
        
        // requests a control activation with the given value and priority
        void request (T& value, int priority=0);
                
        // Checks if the control is activated.  If so the requested value is returned and the control is deactivated.
        bool checkRequested (T& value);
        
        // just gets the last requested value
        void getValue (T& value);
};

// note: DEFINITIONS OF TEMPLATE CLASSES MUST BE PLACED IN HEADER

// Constructor
template <typename T>
ControlT2<T>::ControlT2()
{        
    brequested = false;
    reqPriority = 0;
}
    
template <typename T>
void ControlT2<T>::request(T& value, int priority)
{  
    std::lock_guard<std::mutex> locker(mutex);
    // accept request only if matches present control priority
    if (priority >= reqPriority)
    {
        brequested = true;
        this->value = value;    
        reqPriority = priority;
    }
}

template <typename T>
bool ControlT2<T>::checkRequested(T& value)
{
    std::lock_guard<std::mutex> locker(mutex);
    
    if (brequested)
    {
        value = this->value;
        brequested = false;
        reqPriority = 0;
        return true;
    }
    else
        return false;
}

template <typename T>
void ControlT2<T>::getValue(T& value)
{
    std::lock_guard<std::mutex> locker(mutex);
    
    value = this->value;
}

}    
}
#endif
