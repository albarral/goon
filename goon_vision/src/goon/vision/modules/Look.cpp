/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h> // for sleep
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
        setState(Look::eSTATE_WAIT);
        
        wait4FocusBeat();
        oCortexVision.init(pVisualData->getScene());
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
        case Look::eSTATE_WAIT:
            
            clearObject();
            //changeFocus();
            break;

//        case eSTATE_NEW_FOCUS:
//            
//            bindObject();
//            //identifyObject();
//            setState(eSTATE_IDENTIFY);
//            break;

        case Look::eSTATE_IDENTIFY:

            bindObject();
            //identifyObject();        
            LOG4CXX_TRACE(logger, "clone object ... ");
            pVisualData->updateObject2(oCortexVision.getObject());

            break;
    }   // end switch        
    
    // produce new beat
    newBeat();    
    writeBus();
}

//bool Look::changeFocus()
//{
//    pGoonBus->getCO_FOCUS_SHIFT().request();
//    pGoonBus->getCO_FOCUS_MODE().request(Focus::eSEARCH_SALIENCY);
//    return true;
//}

void Look::clearObject()
{
    // clear object if not done before
    if (lookedObject != -1)
    {
        oCortexVision.getObject().clear();
        lookedObject = -1;
    }    
}

void Look::bindObject()
{  
    // get updated copy of retina & rois
    pVisualData->getRetinaCopy(oCortexVision.getRetina());
    pVisualData->getROIsCopy(oCortexVision.getROIs());
    
    LOG4CXX_DEBUG(logger, "binding ... ");    
    oCortexVision.formObject(focusedROI);
    
    LOG4CXX_DEBUG(logger, "characterization ... ");    
    oCortexVision.analyseObject();
    
    //LOG4CXX_DEBUG(logger, oCortexVision.getObject().shortDesc());    
}

void Look::identifyObject()
{
    LOG4CXX_DEBUG(logger, "identify object -> TO DO");
    // get identified object ID 
    lookedObject = oCortexVision.getObject().getID();
}

void Look::senseBus()
{
    // if target focused, analyze it
    if (pGoonBus->getSO_FOCUS_FOCUSED().getValue())
    {
        focusedROI = pGoonBus->getSO_FOCUS_ROI().getValue();
        setState(Look::eSTATE_IDENTIFY);            
    }
    // otherwise wait
    else
        setState(Look::eSTATE_WAIT);    
}

void Look::writeBus()
{
    pGoonBus->getSO_LOOK_OBJECT().setValue(lookedObject);    
    pGoonBus->getSO_LOOK_BEAT().setValue(beat);
}

void Look::wait4FocusBeat()
{
    LOG4CXX_INFO(logger, "wait first focus beat");     
    while (pGoonBus->getSO_FOCUS_BEAT().getValue() == 0)            
        usleep(50000);  // 50 ms
}

void Look::showState()
{
    switch (getState())
    {
        case eSTATE_WAIT:
            LOG4CXX_INFO(logger, ">> wait");
            break;
//        case eSTATE_NEW_FOCUS:
//            LOG4CXX_INFO(logger, ">> new focus");
//            break;
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