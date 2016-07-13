#ifndef __GOON_LOOK_MONITOR_H
#define __GOON_LOOK_MONITOR_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include <opencv2/opencv.hpp>

#include "goon/utils/Module.h"
#include "goon/look/bus/LookBus.h"
#include "goon/data/capture.h"
#include "goon/data/visual_data.h"
#include "goon/monitor/RetinaMonitor.h"
#include "goon/monitor/ROIsMonitor.h"
#include "goon/monitor/RetinaSaver.h"
#include "goon/show/DualWindow.h"

namespace goon
{
// Monitoring module of the look process
class LookMonitor: public Module
{
private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    // shared data
    LookBus* pLookBus;        // access to the internal bus     
    Capture* pCapture;           // access pointer to capture data
    VisualData* pVisualData;    // access pointer to visual data
    // logic
    cv::Mat imageCam;
    cv::Mat imageRetina;
    cv::Mat imageROIs;
    RetinaMonitor oRetinaMonitor;
    ROIsMonitor oROIsMonitor;
    DualWindow oDualWindow; 
    int frameNum;
    int seeBeat;        // See module's beat
    
public:
    LookMonitor();
    ~LookMonitor();

    // initializes the module 
    void init(Capture& oCapture, VisualData& oVisualData, LookBus& oLookBus);   
    
    // first action after thread begins 
    virtual void first();
    // loops inside the thread 
    virtual void loop();            
    // last action before thread ends
    virtual void bye();
    
    // just one loop exectution (for testing)
    void oneShot();
};

}
#endif
