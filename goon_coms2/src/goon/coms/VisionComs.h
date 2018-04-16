#ifndef __GOON_COMS_VISIONCOMS_H
#define __GOON_COMS_VISIONCOMS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/coms/modules/VisionServer.h"
#include "goon/core/GoonBus.h"

namespace goon
{
class VisionComs
{
private:    
    static log4cxx::LoggerPtr logger;      
    VisionServer oVisionServer;           // vision server module    

public:
  VisionComs();
  ~VisionComs();

   // launches the coms modules
   bool launch(GoonBus& oGoonBus);
   // ends the coms modules
   bool end();
   
    // checks if amy end has been requested
    bool checkGoonEndRequested();      
};
}		

#endif
