#ifndef __GOON_COMS_GoonListener_H
#define __GOON_COMS_GoonListener_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "goon/core/GoonBus.h"
#include "goon/coms/in/ComsInGoonControl.h"
#include "nety/NetNodeServer.h"
#include "tuly/control/module2.h"

namespace goon
{
// This module listens to external control requests for goon process.
// It uses nety server nodes for communications.
class GoonListener : public tuly::Module2
{
private:
    static log4cxx::LoggerPtr logger;
    std::string modName;          // module name
    bool benabled;
    // logic
    nety::NetNodeServer oNetyServerExtra;      // communications server for extra category
    ComsInGoonControl oCIGoonControl;         // object that gets talky commands and transforms them to bus control values
    bool brequestedGoonEnd;

public:
    GoonListener();
    //~GoonListener();

    void init(GoonBus& oGoonBus);       
    bool isEnabled() {return benabled;};
        
    // check special actions
    bool checkSpecialActions();    
    bool getGoonEndRequested() {return brequestedGoonEnd;};
        
private:
    virtual void first();
    // executes the behaviour
    virtual void loop();
    // check given server for received messages and process them
    void checkServer(nety::NetNodeServer& oNetyServer);
};
}		
#endif
