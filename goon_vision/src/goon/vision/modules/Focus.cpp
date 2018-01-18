/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

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
    
    // start in SEARCH state
    if (benabled)
    {
        LOG4CXX_INFO(logger, "started");  
        targetROI = -1;
        setState(Focus::eSTATE_SEARCH);
 
        // default search mode ...
        // by saliency
        mode = Focus::eSEARCH_SALIENCY;
        // by position near to (320,240)
//        mode = Focus::eSEARCH_POSITION;        
//        features[0] = 320;
//        features[1] = 240;        
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
// The target selection is done in the way defined by the present search mode (see enum eModes).
// FUTURE: An inhibition of return mechanism should avoid repeating past selections, allowing the focus to always explore new rois.
// If a new target roi is selected the function returns true. Otherwise false is returned.
bool Focus::selectTarget()
{
    LOG4CXX_DEBUG(logger, "select target ... ");

    Rois& oROIs2 = pVisualData->getROIs2();
    if (oROIs2.getList().empty())
    {
        LOG4CXX_WARN(logger, "can't select target, no ROIs detected!");
        return false;
    }
    
    switch (mode)
    {
        case Focus::eSEARCH_SALIENCY:
            // set saliency mode (color by default)
            oSaliency.setMode(Saliency::eSALIENCY_COLOR);   
            oSaliency.computeSaliency(oROIs2.getList());
            targetROI = oSaliency.getMostSalient().roiID;
            break;

        case Focus::eSEARCH_POSITION:
            targetROI = selectTargetByPosition(oROIs2.getList());
            break;
                        
        default:
            LOG4CXX_WARN(logger, "can't select target, search mode not implemented ");
            targetROI = -1;
            break;
    }
    
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
    LOG4CXX_WARN(logger, "detect target -> TO DO");
    // TO DO ...
    return false;
}

// An interest measure is used to select big rois near a defined position.
int Focus::selectTargetByPosition(std::list<ROI>& listROIs)
{
    float interest, maxInterest = 0.0;
    int winner = -1;
    // get ROI with max interest 
    for (ROI& oROI : listROIs) 
    {
        float xdif = oROI.getPos()[0] - features[0];
        float ydif = oROI.getPos()[1] - features[1];
        // avoid division by 0
        if (xdif == 0) xdif = 1;
        if (ydif == 0) ydif = 1;

        // interest = mass/distance
        interest = (float)oROI.getMass() / (xdif*xdif + ydif*ydif);
        if (interest > maxInterest) 
        {
            winner = oROI.getID();
            maxInterest = interest;
        }
    }
    
    return winner;
}

void Focus::senseBus()
{
    // search mode
    if (pGoonBus->getCO_FOCUS_MODE().checkRequested())
    {
        int value = pGoonBus->getCO_FOCUS_MODE().getValue();
        // if valid mode -> LAUNCH movement
        if (value >= 0 && value < Focus::eSEARCH_DIM)
        {
            mode = value;
            LOG4CXX_INFO(logger, modName << " new search mode " + std::to_string(mode));                     
        }
        else
            LOG4CXX_WARN(logger, modName << " invalid search mode " + std::to_string(mode));                     
    }
        
    // search features
    if (pGoonBus->getCO_FOCUS_SEARCH_VALUE().checkRequested())
    {  
        features = pGoonBus->getCO_FOCUS_SEARCH_VALUE().getValue();
        LOG4CXX_INFO(logger, modName << " search features = " + std::to_string(features[0]) + ", " + std::to_string(features[1]) + ", " + std::to_string(features[2]));                     
    }

    // if shift requested -> SEARCH
    if (pGoonBus->getCO_FOCUS_SHIFT().checkRequested())
        setState(eSTATE_SEARCH);
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