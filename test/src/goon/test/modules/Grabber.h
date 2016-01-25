#ifndef __GOON_TEST_GRABBER_H
#define __GOON_TEST_GRABBER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <log4cxx/logger.h>

#include "goon/test/Module.h"
#include "goon/camera/camera.h"
#include "goon/data/visual_data.h"

namespace goon
{    
// Module in charge of grabbing images from the camera
class Grabber : public Module
{
public:
    // states of Grabber module
    enum eState
    {
        eSTATE_ON
    };

private:
    static log4cxx::LoggerPtr logger;
    bool binitialized;
    Camera* oCamera;
    VisualData* pVisualData;        // shared data

public:
    Grabber();
    ~Grabber();
    
    // initializes the module 
    void init(VisualData& oVisualData, int workingCamera);   
       
private:
    // first action after thread begins 
    virtual void first();
    // loop inside the module thread 
    virtual void loop();             
    // last action before thread ends
    virtual void bye();
};

}
#endif
