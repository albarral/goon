#ifndef __GOON_SHOW_GOONSHOW_H
#define __GOON_SHOW_GOONSHOW_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/core/GoonBus.h"
#include "goon/core/Capture.h"
#include "goon/core/VisualData.h"
#include "goon/show/modules/ShowRetina.h"

namespace goon
{
// Manager of goon show modules
class GoonShow
{
private:
    static log4cxx::LoggerPtr logger;
    bool blaunched;     // indicates when the manager has been launched       
    // modules
    ShowRetina oShowRetina;
    
public:
    GoonShow();
    ~GoonShow();

    bool launch(GoonBus& oGoonBus, VisualData& oVisualData, Capture& oCapture);
    void end();    
    
    // just one loop execution (for testing)
    void oneShot(GoonBus& oGoonBus, VisualData& oVisualData, Capture& oCapture);
};

}
#endif
