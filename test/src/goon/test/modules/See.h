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
#include "goon/data/visual_data.h"
#include "goon/data/retina.h"

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
    VisualData* pVisualData;        // shared data
    cv::Mat imageCam;
    // for debug
    std::mutex mutex;
    int counter;
    Retina oRetina2;

public:
    See();
    ~See();
    
    // initializes the module 
    void init(VisualData& oVisualData);   
    
    int getCounter();
    Retina& getRetina2();    
       
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
