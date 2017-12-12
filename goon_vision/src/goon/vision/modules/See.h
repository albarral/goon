#ifndef __GOON_VISION_SEE_H
#define __GOON_VISION_SEE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>
#include <opencv2/opencv.hpp>

#include "goon/core/GoonBus.h"
#include "goon/core/Capture.h"
#include "goon/core/VisualData.h"
#include "goon/retinal/retinal_vision.h"
#include "goon/peripheral/peripheral_vision.h"
#include "tuly/control/module3.h"
#include "maty/math/Click.h"

namespace goon
{    
// Module in charge of processing the camera images.
// Performs retinal and peripheral vision processes..    
class See : public tuly::Module3
{
public:
    // states of See module
    enum eState
    {
        eSTATE_ON
    };

private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    int beat;   // module's beat
    // shared data
    GoonBus* pGoonBus;        // access to the internal bus     
    Capture* pCapture;           // access pointer to capture data
    VisualData* pVisualData;    // access pointer to visual data
    // logic
    RetinalVision* oRetinalVision;
    PeripheralVision* oPeripheralVision;
    cv::Mat imageCam;     
    float fps;     // processing speed
    maty::Click oClick;

public:
    See();
    ~See();
    
    // initializes the module 
    void init(Capture& oCapture, VisualData& oVisualData, GoonBus& oLookBus);   
    
    // just one loop exectution (for testing)
    void oneShot();       

private:
    // first action after thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    // last action before thread ends
    virtual void bye();
    
    // waits till there's a valid image in the shared visual data (used for retinal vision size initialization)
    void wait4ValidImage();
};

}
#endif
