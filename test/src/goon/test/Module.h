#ifndef __SAM_UTILS_MODULE_H
#define __SAM_UTILS_MODULE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <thread>
#include <mutex>

namespace goon
{    
// Base class designed to run a module inside its own thread.
// Derived classes must implement 3 methods: first(), loop() and bye().
// For starting & stopping the module use the following methods:
// - on() -> starts the module.
// - off()  -> asks the module to stop.
// - wait() -> waits till the thread is finished.
// Thread safety implemented.    
class Module 
{
public:
        static const int state_OFF = 99;
        static const int state_UNKNOWN = 100;
private:
        std::mutex mutex;
        std::thread t;        // module thread       
        int state;             // module present state
        int prevState;       // module previous state
        int period;           // time (microseconds) to be slept between loop executions
        bool bOffRequested; // off state requested (module asked to stop)

public:
        Module();
                
        // starts the thread
        void on();                
        // asks the thread to stop
        void off();        
        // waits till the thread is finished
        void wait();
        
        // sets the desired loop frequency 
        void setFrequency(float fps);
        // gets the loop frequency 
        float getFrequency();

        // checks the module state
        int getState();
        // gets the previous state
        int getPrevState();
        
        // checks if module is OFF
        bool isOff();
        
protected:
        // method running inside the thread 
        void run();
        // checks if off was requested and clears the request
        bool isOffRequested();     
        
        // first action after thread begins 
        virtual void first() = 0;
        // loops inside the thread 
        virtual void loop() = 0;            
        // last action before thread ends
        virtual void bye() = 0;
        
        // sets the state (also stores previous state)
        void setState(int value);
        // sets the previous state (usually not needed as this is done automatically by setState)
        void setPrevState(int value);
        // checks if state differs from previous one
        bool isStateChanged();
        
private:
        // sets the next state (ignoring the OFF limitation) 
        //void forceNextState(int state);
    
};
}    
#endif
