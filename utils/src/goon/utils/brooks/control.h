#ifndef _GOON_BROOKS_CONTROL_H
#define _GOON_BROOKS_CONTROL_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>

namespace goon 
{
namespace brooks
{
// This class implements a basic control command inside a control architecture.
// A flag is raised whenever the command is requested, and it is lowered down whenever the command state is checked. 
// Thread safety implemented.
class Control 
{
    protected:
        bool brequested;           // command requested flag        
        std::mutex mutex1;

    public:
        Control();
        //~Control();
                        
        // Requests the execution of the control command.
        void request();

        // Checks if a command request is pending to be executed.
        // After the check, the request is considered not pending anymore.
        virtual bool checkRequested();
};

}
}    
#endif
