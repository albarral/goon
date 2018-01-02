/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include "log4cxx/ndc.h"

#include "goon/vision/modules/Focus.h"
#include "goon/data/base/roi.h"

namespace goon
{    
log4cxx::LoggerPtr Focus::logger(log4cxx::Logger::getLogger("goon.vision.focus"));

Focus::Focus() 
{
    modName = "Focus";
}
  
void Focus::showInitialized()
{
    LOG4CXX_INFO(logger, modName + " initialized");             
};

void Focus::first()
{    
    log4cxx::NDC::push("Focus");   	
    
    // we start in LOST state
    if (benabled)
    {
        LOG4CXX_INFO(logger, "started");  
        setState(Focus::eSTATE_SEARCH);
        // default search mode by position
        mode = Focus::eSEARCH_POSITION;        
        // TEST features
        features[0] = 320;
        features[1] = 240;        
        targetROI = -1;
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized Going off ... ");  
        tuly::Module3::off();        
    }
}

void Focus::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void Focus::loop()
{   
    senseBus();
    
    // skip if module is inhibited
//    if (binhibited)            
//        return;

    if (isStateChanged())
        showState();

    switch (getState())
    {
        case eSTATE_SEARCH:
            
            if (selectTarget())
            {
                setState(eSTATE_TRACK);
                LOG4CXX_WARN(logger, "new target selected -> ROI " << targetROI);                
            }
            else
                LOG4CXX_WARN(logger, "target selection failed");                                
            break;

        case eSTATE_TRACK:
            
            if (followTarget())
            {
//                // if slow target, focus in it
//                if (!isTargetMovingFast (loop_time))
//                {
//                    changeState(eSTATE_FOCUSED);
//                    LOG4CXX_INFO(logger, "*** FOCUSED");
//                }
            }
            // if target lost
            else
                setState(eSTATE_LOST);
            break;


        case eSTATE_LOST:

            // if target recovered
            if (detectTarget())
            {
                LOG4CXX_INFO(logger, "target recovered -> ROI " << targetROI);
                setState(eSTATE_TRACK);
            }
            else
                setState(eSTATE_SEARCH);                
            break;
    }   // end switch        
    
    // produce new beat
    newBeat();
    
    writeBus();
}

// This function searches the visual field for the next target ROI.
// An interest measure is used that favours the selection of big rois that are near to the specified central position.
// An inhibition of return mechanism avoids repeating past selections, allowing the focus to always explore new rois.
// If a new target roi is selected the function returns true. Otherwise false is returned.
bool Focus::selectTarget()
{
    float interest, maxInterest;
    int winner;

    LOG4CXX_DEBUG(logger, "select target ... ");

    Rois& oROIs2 = pVisualData->getROIs2();
    winner = -1;
    maxInterest = 0.0;
    // get ROI with max interest
    for (ROI& oROI : oROIs2.getList()) 
    {
        interest = computeInterest(oROI);

        if (interest > maxInterest) 
        {
            winner = oROI.getID();
            maxInterest = interest;
        }
    }

    targetROI = winner;
    return (targetROI != -1);
}

// This function follows the target, checking if the target ROI still exists.
bool Focus::followTarget()
{
    bool bfound = pVisualData->getROIs2().isROIStillActive(targetROI);

    return bfound;
}

bool Focus::detectTarget()
{
    // TO DO ...
    return false;
}

float Focus::computeInterest(ROI& oROI)
{
    float interest = 0.0;
    
    if (mode == Focus::eSEARCH_POSITION)
    {
        float xdif = oROI.getPos()[0] - features[0];
        float ydif = oROI.getPos()[1] - features[1];

        // avoid division by 0
        if (xdif == 0)
            xdif = 1;
        if (ydif == 0)
            ydif = 1;

        interest = ((float)oROI.getMass() / (xdif*xdif + ydif*ydif));
    }
    
    return interest;
}

void Focus::senseBus()
{
    // search mode
    if (pGoonBus->getCO_FOCUS_MODE().checkRequested())
    {
        mode = pGoonBus->getCO_FOCUS_MODE().getValue();
        // if valid mode -> LAUNCH movement
        if (mode >= 0 && mode < Focus::eSEARCH_DIM)
        {
            LOG4CXX_INFO(logger, modName << " new search mode " + std::to_string(mode));                     
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid search mode requested " + std::to_string(mode));                     
    }
        
    // search features
    if (pGoonBus->getCO_FOCUS_SEARCH_V0().checkRequested())
    {  
        features[0] = pGoonBus->getCO_FOCUS_SEARCH_V0().getValue();
        LOG4CXX_INFO(logger, modName << " search feature 0 = " + std::to_string(features[0]));                     
    }
    if (pGoonBus->getCO_FOCUS_SEARCH_V1().checkRequested())
    {  
        features[1] = pGoonBus->getCO_FOCUS_SEARCH_V1().getValue();
        LOG4CXX_INFO(logger, modName << " search feature 1 = " + std::to_string(features[1]));                     
    }
    if (pGoonBus->getCO_FOCUS_SEARCH_V2().checkRequested())
    {  
        features[2] = pGoonBus->getCO_FOCUS_SEARCH_V2().getValue();
        LOG4CXX_INFO(logger, modName << " search feature 2 = " + std::to_string(features[2]));                     
    }

    // if shift requested -> SEARCH
    if (pGoonBus->getCO_FOCUS_SHIFT().checkRequested())
    {
        setState(eSTATE_SEARCH);
    }
}

void Focus::writeBus()
{
    pGoonBus->getSO_FOCUS_BEAT().setValue(beat);
    pGoonBus->getSO_FOCUS_ROI().setValue(targetROI);
}

void Focus::showState()
{
    switch (getState())
    {
        case eSTATE_SEARCH:
            LOG4CXX_INFO(logger, ">> search");
            break;
        case eSTATE_TRACK:
            LOG4CXX_INFO(logger, ">> track");
            break;
        case eSTATE_LOST:
            LOG4CXX_INFO(logger, ">> lost");
            break;
    }   // end switch    
}
        

// just one loop execution (for testing)
void Focus::oneShot()
{
    first();
    loop();
    bye();
}

}