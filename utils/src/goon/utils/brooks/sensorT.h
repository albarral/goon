#ifndef _GOON_BROOKS_SENSORT_H
#define _GOON_BROOKS_SENSORT_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

namespace goon 
{
namespace brooks
{
// This class implements a Brooks sensor.
// Thread safety implemented.
template <typename T>
class SensorT 
{
    private:
        std::mutex mutex;
        T value;

    public:
        SensorT();
        //~SensorT();
                        
        // Sets the sensor info
        void setValue(T value);
        
        // Gets the sensor info
        T& getValue();
};

// note: DEFINITIONS OF TEMPLATE CLASSES MUST BE PLACED IN HEADER

// Constructor
template <typename T>
SensorT<T>::SensorT ()
{    
}

template <typename T>
void SensorT<T>::setValue(T value)
{
    std::lock_guard<std::mutex> locker(mutex);
    this->value = value;
}

template <typename T>
T& SensorT<T>::getValue()
{
    std::lock_guard<std::mutex> locker(mutex);
    return value;
}

}    
}
#endif
