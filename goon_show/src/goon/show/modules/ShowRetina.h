#ifndef __GOON_SHOW_SHOWRETINA_H
#define __GOON_SHOW_SHOWRETINA_H

/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include <opencv2/opencv.hpp>

#include "tuly/control/module3.h"
#include "goon/core/GoonBus.h"
#include "goon/core/Capture.h"
#include "goon/core/VisualData.h"
#include "goon/show/monitor/RetinaMonitor.h"
#include "goon/show/monitor/ROIsMonitor.h"
#include "goon/show/monitor/RetinaSaver.h"
#include "tivy/DualWindow.h"

namespace goon
{
// Monitoring module of the goon vision process
class ShowRetina: public tuly::Module3
{
private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    // shared data
    GoonBus* pGoonBus;        // access to the internal bus     
    Capture* pCapture;           // access pointer to capture data
    VisualData* pVisualData;    // access pointer to visual data
    // logic
    cv::Mat imageCam;
    cv::Mat imageRetina;
    cv::Mat imageROIs;
    RetinaMonitor oRetinaMonitor;
    ROIsMonitor oROIsMonitor;
    tivy::DualWindow oDualWindow; 
    std::string windowName;
    int frameNum;
    int seeBeat;        // See module's beat
    
public:
    ShowRetina();
    ~ShowRetina();

    // initializes the module 
    void init(Capture& oCapture, VisualData& oVisualData, GoonBus& oGoonBus);   
    
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
