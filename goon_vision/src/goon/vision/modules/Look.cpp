/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "log4cxx/ndc.h"

#include "goon/vision/modules/Look.h"
#include "goon/vision/modules/Focus.h"
#include "goon/data/base/roi.h"

namespace goon
{    
log4cxx::LoggerPtr Look::logger(log4cxx::Logger::getLogger("goon.vision.look"));

Look::Look() 
{
    modName = "Look";
}
  
void Look::showInitialized()
{
    LOG4CXX_INFO(logger, modName + " initialized");             
};

void Look::first()
{    
    log4cxx::NDC::push("Look");   	
    
    // we start in SEARCH state
    if (benabled)
    {
        LOG4CXX_INFO(logger, "started");  
        setState(Look::eSTATE_SEARCH);
        
        oCortexVision.init(pVisualData->getRetina(), pVisualData->getROIs(), pVisualData->getScene());
        focusedROI = -1;
        lookedObject = -1;
    }
    // if not initialized -> OFF
    else
    {
        LOG4CXX_WARN(logger, "NOT initialized Going off ... ");  
        tuly::Module3::off();        
    }
}

void Look::bye()
{
    LOG4CXX_INFO(logger, "ended");     
}

void Look::loop()
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
            
            changeFocus();
            break;

        case eSTATE_NEW_FOCUS:
            
            LOG4CXX_INFO(logger, "ROI " << focusedROI);  
            bindObject();
            identifyObject();
            setState(eSTATE_IDENTIFY);
            break;


        case eSTATE_IDENTIFY:

            bindObject();
            identifyObject();
            break;
    }   // end switch        
    
    // produce new beat
    newBeat();
    
    writeBus();
}

bool Look::changeFocus()
{
    pGoonBus->getCO_FOCUS_SHIFT().request();
    pGoonBus->getCO_FOCUS_MODE().request(Focus::eSEARCH_SALIENCY);
    return true;
}

bool Look::bindObject()
{    
    LOG4CXX_DEBUG(logger, "binding ... ");    
    oCortexVision.formObject(focusedROI);
    LOG4CXX_DEBUG(logger, "characterization ... ");    
    oCortexVision.analyseObject();
    
    LOG4CXX_TRACE(logger, "clone object ... ");
    pVisualData->cloneObject(oCortexVision.getObject());

    LOG4CXX_DEBUG(logger, oCortexVision.getObject().shortDesc());    

    return true;
}

bool Look::identifyObject()
{
    LOG4CXX_DEBUG(logger, "identify object -> TO DO");
    return true;
}


void Look::senseBus()
{
    // if focused ROI has changed
    if (focusedROI != pGoonBus->getSO_FOCUS_ROI().getValue())
    {
        focusedROI = pGoonBus->getSO_FOCUS_ROI().getValue();
        // if focus lost -> search new target
        if (focusedROI == -1)
            setState(eSTATE_SEARCH);    
        // if focus set -> analyze new object
        else
            setState(eSTATE_NEW_FOCUS);        
    }
}

void Look::writeBus()
{
    pGoonBus->getSO_LOOK_OBJECT().setValue(lookedObject);    
    pGoonBus->getSO_LOOK_BEAT().setValue(beat);
}

void Look::showState()
{
    switch (getState())
    {
        case eSTATE_SEARCH:
            LOG4CXX_INFO(logger, ">> search");
            break;
        case eSTATE_NEW_FOCUS:
            LOG4CXX_INFO(logger, ">> new focus");
            break;
        case eSTATE_IDENTIFY:
            LOG4CXX_INFO(logger, ">> identify");
            break;
    }   // end switch    
}
        

// just one loop execution (for testing)
void Look::oneShot()
{
    first();
    loop();
    bye();
}

}