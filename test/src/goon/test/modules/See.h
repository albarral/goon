#ifndef __GOON_TEST_SEE_H
#define __GOON_TEST_SEE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <string>
#include <log4cxx/logger.h>
#include <opencv2/opencv.hpp>

#include "goon/test/Module.h"
#include "goon/retinal/retinal_vision.h"
#include "goon/peripheral/peripheral_vision.h"
#include "goon/data/capture.h"
#include "goon/data/visual_data.h"
#include "goon/data/retina.h"   // for debug
#include "goon/data/rois.h"     // for debug
#include "goon/utils/Click.h"

namespace goon
{    
// Module in charge of processing the camera images.
// Performs retinal and peripheral vision processes..    
class See : public Module
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
    RetinalVision* oRetinalVision;
    PeripheralVision* oPeripheralVision;
    Capture* pCapture;              // shared data
    VisualData* pVisualData;        // shared data
    cv::Mat imageCam;
     // processing speed
    float fps;     
    utils::Click oClick;
    // for debug
    std::mutex mutex;
    int counter;
    Retina oRetina2;            
    Rois oROIs2;        

public:
    See();
    ~See();
    
    // initializes the module 
    void init(Capture& oCapture, VisualData& oVisualData);   
    
    // all mutex protected
    int getCounter();
    Retina& getRetina2();    
    Rois& getROIs2();
    float getFps();

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
