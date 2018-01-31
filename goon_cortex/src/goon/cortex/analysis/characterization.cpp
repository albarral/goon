/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/
  
#include <vector>
#include <opencv2/core/core.hpp>

#include "goon/cortex/analysis/characterization.h"
#include "goon/features/Body.h"
#include "goon/features/structure/Structure2.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr Characterization::logger(Logger::getLogger("goon.cortex.characterization"));

// constructor
Characterization::Characterization()
{
}


void Characterization::checkGlobalObject(Object& oObject)
{
    LOG4CXX_TRACE(logger, "Characterization.checkGlobalObject");
        
    // compute object's shape
    oObject.computeBasicShape();
    oObject.computeComplexShape();            
}


void Characterization::checkObjectDetails(Object& oObject)
{
    LOG4CXX_TRACE(logger, "Characterization.checkObjectDetails");
    
    // compute shapes of all object's components
    for (Body& oBody : oObject.getSubBodies())
    {
        oBody.computeBasicShape();
        oBody.computeComplexShape();
    }

    // and compute object structure ...
    
    // set object as structure reference
    cv::Point centroid(oObject.getPos()[0], oObject.getPos()[1]);
    Structure2& oStructure = oObject.getStructure();
    oStructure.setReference(centroid, oObject.getCovariances(), oObject.getMass());
    
    // get list of elements for the structure
    std::vector<cv::Vec3i> listElements;
    for (Body& oBody : oObject.getSubBodies())
    {
        cv::Vec3i element(oBody.getPos()[0], oBody.getPos()[1], oBody.getMass());
        listElements.push_back(element);
    }    
    
    // and compute it
    oStructure.computeStructure(listElements);
}
				 
}

