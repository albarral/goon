#ifndef _GOON_BROOKS_INHIBITION_H
#define _GOON_BROOKS_INHIBITION_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

namespace goon 
{
namespace brooks
{    
// Implements the inhibition mechanism in Brooks subsumption architecture.
// Higher level modules inhibit lower level modules during short periods of time.
// When a request arrives the inhibition is activated for the specified time period (in loops).
// Everytime the inhibition state is checked the loops counter is decreased. 
// When it reaches 0 the inhibition is deactivated.
class Inhibition 
{
    protected:
        int loops;           // inhibition period (in loops)
        std::mutex mutex;

    public:
        Inhibition();
        //~Inhibition();
                        
        // Activates the inhibition for the given time period (in loops).
        void request(int loops);

        // Checks if the inhibition is active.
        bool isRequested();
};
}
}    
#endif
