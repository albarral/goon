#ifndef __GOON_MAIN_GOONCONTROL_H
#define __GOON_MAIN_GOONCONTROL_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/core/GoonBus.h"
#include "goon/core/Capture.h"
#include "goon/core/VisualData.h"
#include "goon/vision/VisionManager.h"
#include "goon/show/GoonShow.h"

namespace goon
{
// This class is used to control a robot's arms & hands.
// It instantiates the control bus and launches the arms & hands managers.
class GoonControl
{
    
private:
    static log4cxx::LoggerPtr logger;
    GoonBus oGoonBus;                            // arm bus
    VisualData oVisualData;    
    Capture oCapture;
    VisionManager oVisionManager;
//  GoonComs oGoonComs;
    GoonShow oGoonShow;

public:
    GoonControl();
    ~GoonControl();

    // launches the goon modules
    bool launch();
    // ends the goon modules
    bool end();
    // one shot test
    void oneShot(int testCamera);

    // checks if finish command has been requested from console
    bool checkEndRequested();        

    // shows the present values of all bus elements
    void showBusState();

    // access bus (JUST FOR TEST)
    GoonBus& getGoonBus4Test() {return oGoonBus;};
};

}    
#endif
