#ifndef __GOON_COMS_IN_ARMCONTROL_H
#define __GOON_COMS_IN_ARMCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/core/GoonBus.h"
#include "talky/coms/Command.h"
#include "tuly/utils/IntegerQueue.h"

namespace goon
{
// Class used to process goon control requests.
// Requests are converted to proper bus signals.
class ComsInGoonControl 
{    
public:
    // special actions
    enum eAction
    {
         eACTION_GOON_END,            // end goon process
    };

private:
    static log4cxx::LoggerPtr logger;            
    GoonBus* pGoonBus;      // access to goon bus
    tuly::IntegerQueue oQueueSpecialActions;  // queue of special actions
    
public:
    ComsInGoonControl();
    //~ComsArmControl();
    
    void connect2Arm(GoonBus* pGoonBus);

   // transforms command into proper call to arm interface
    bool processCommand(talky::Command& oCommand);
    
    tuly::IntegerQueue& getQueueSpecialActions() {return oQueueSpecialActions;}
    
private:
    // process command of extra category
    bool processExtraCommand(talky::Command& oCommand);

    // dummy method for to do commands
    void toDoCommand(float value);
};
}
#endif
