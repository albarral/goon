#ifndef __GOON_CORE_GOONMODULE_H
#define __GOON_CORE_GOONMODULE_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/core/GoonBus.h"
#include "goon/core/VisualData.h"
#include <tron/control/module3.h>

namespace goon
{
// Base class for goon modules.
// It has access pointers to goon bus and goon visual data.
class GoonModule : public tron::Module3
{
protected:
    bool benabled;
    int beat;   // module's beat
    // shared data
    GoonBus* pGoonBus;        // access to the internal bus     
    VisualData* pVisualData;    // access pointer to visual data

public:
    GoonModule();
    //~GoonModule();

    bool isEnabled() {return benabled;};    
    // initialize module
    virtual void init(GoonBus& oGoonBus, VisualData& oVisualData);               
    
protected:
    // show module initialization in logs
    virtual void showInitialized() = 0;
    // set new beat
    void newBeat();

};
}		
#endif
