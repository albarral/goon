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
        
        // connect led to Focus beat sensor
        oFocusBeatLed.init(pGoonBus->getSO_FOCUS_BEAT());        
        wait4FocusBeat();
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

    // if Focus beat not changed, skip
    if (!oFocusBeatLed.check())
        return;

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

            formObject();
            identifyObject();        
            LOG4CXX_TRACE(logger, "clone object ... ");
            pVisualData->updateObject2(oObject);

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
        oObject.clear();
        lookedObject = -1;
    }    
}

void Look::formObject()
{  
    // get updated copy of retina & rois
    pVisualData->getRetinaCopy(oCortexVision.getRetina());
    pVisualData->getROIsCopy(oCortexVision.getROIs());
    
    LOG4CXX_DEBUG(logger, "bind ... ");    
    oCortexVision.formObject(oObject, focusedROI);
    
    LOG4CXX_DEBUG(logger, "model ... ");    
    oCortexVision.modelObject(oObject);
    
    //LOG4CXX_DEBUG(logger, oCortexVision.getObject().shortDesc());    
}

void Look::identifyObject()
{
    LOG4CXX_DEBUG(logger, "identify ...");
    // identify 
    if (!oCortexVision.identifyObject(oObject))
        // memorize object if identification fails    
        oCortexVision.memorizeObject();
    
    // get identified object ID 
    lookedObject = oObject.getID();
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
    // wait while Focus beat not changed
    while (!oFocusBeatLed.check())            
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