/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>

#include "goon/cortex/analysis/binding.h"
#include "goon/cortex/ConfigCortex.h"	
#include "maty/math/area.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr Binding::logger(Logger::getLogger("goon.cortex.binding"));
// constructor
Binding::Binding ()
{
    ConfigCortex oConfigCortex;
    bindObjectFraction = oConfigCortex.getBINDING_OVERLAP_FRACTION();
}


// destructor
//Binding::~Binding()
//{
//}


// This function builds the landmark from the regions inside the roi's window.
// The landmark's mask is built from them.
void Binding::formObject(Object& oObject, Retina& oRetina, cv::Rect& window)
{
    LOG4CXX_TRACE(logger, "Binding::formObject");
    
    // reset object
    oObject.clear();
    
    float overlap;
    std::list<Region>::iterator it_region = oRetina.getListRegions().begin();
    std::list<Region>::iterator it_end = oRetina.getListRegions().end();
    // walk all retina regions 
    while (it_region != it_end)
    {                         
        overlap = maty::Area::getWindowOverlap(window, it_region->getWindow());

        // adding regions that lay inside the specified window to object
        if (overlap > bindObjectFraction)
        {
            // merge region to object
            oObject.merge(*it_region);
            // and add region as component
            oObject.addSubBody(*it_region);
            LOG4CXX_TRACE(logger, "Binding: + region " << it_region->getID());
        }

        it_region++;
    }
}  
}




