#ifndef __GOON_COMS_GoonComs_H
#define __GOON_COMS_GoonComs_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/coms/modules/GoonListener.h"
#include "goon/core/GoonBus.h"

namespace goon
{
class GoonComs
{
private:    
    static log4cxx::LoggerPtr logger;      
    GoonListener oGoonListener;               // communications module for responding to external requests

public:
  GoonComs();
  ~GoonComs();

   // launches the coms modules
   bool launch(GoonBus& oGoonBus);
   // ends the coms modules
   bool end();
   
    // checks if goon end has been requested
    bool checkGoonEndRequested();      
};
}		

#endif
