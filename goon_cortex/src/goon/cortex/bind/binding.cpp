/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>

#include "goon/cortex/bind/binding.h"
#include "goon/data/base/region.h"
#include "goon/data/config/CortexConfig.h"
#include "maty/math/area.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr Binding::logger(Logger::getLogger("goon.cortex.binding"));
// constructor
Binding::Binding ()
{
    CortexConfig oCortexConfig;
    bindObjectFraction = oCortexConfig.getBINDING_OVERLAP_FRACTION();
}

//Binding::~Binding()
//{
//}

// This function builds the landmark from the regions inside the roi's window.
// The landmark's mask is built from them.
void Binding::formObject(Retina& oRetina, cv::Rect& window, Object& oObject)
{
    LOG4CXX_TRACE(logger, "Binding::formObject");
    
    // reset object
    oObject.clear();
    
    float overlap;
    bool bempty = true;
    std::list<Region>::iterator it_region = oRetina.getListRegions().begin();
    std::list<Region>::iterator it_end = oRetina.getListRegions().end();
    // walk all retina regions 
    while (it_region != it_end)
    {                         
        overlap = maty::Area::getWindowOverlap(window, it_region->getWindow());

        // adding regions that lay inside the specified window to object
        if (overlap > bindObjectFraction)
        {
            Body& oBody = *it_region;
            // first region is assigned to the object
            if (bempty)
            {
                oObject.setBody(oBody);
                bempty = false;
            }
            // next regions are merged
            else
                oObject.merge(oBody);

            // add region as component
            oObject.addSubBody(oBody);
            LOG4CXX_TRACE(logger, "Binding: + region " << it_region->getID());
        }

        it_region++;
    }
}  
}




