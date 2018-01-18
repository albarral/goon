#ifndef __GOON_VISION_SEE_H
#define __GOON_VISION_SEE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>
#include <opencv2/opencv.hpp>

#include "goon/core/GoonModule.h"
#include "goon/retinal/retinal_vision.h"
#include "goon/peripheral/PeripheralVision.h"
#include "maty/math/Click.h"

namespace goon
{    
// Module in charge of processing the camera images.
// Performs retinal and peripheral vision processes..    
class See : public GoonModule
{
public:
    // states of See module
    enum eState
    {
        eSTATE_ON
    };

private:
    static log4cxx::LoggerPtr logger;
    // logic
    RetinalVision oRetinalVision;
    PeripheralVision oPeripheralVision;
    cv::Mat imageCam;     
    float fps;     // processing speed
    maty::Click oClick;

public:
    See();
    //~See();
        
    // just one loop execution (for testing)
    void oneShot();       

private:
    // show module initialization in logs
    virtual void showInitialized();    
    // first action after thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    // last action before thread ends
    virtual void bye();
    
    // waits till there's a valid image in the shared visual data (used for retinal vision size initialization)
    void wait4FirstCapture();
};

}
#endif
