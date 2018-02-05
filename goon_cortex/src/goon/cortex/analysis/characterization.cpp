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
    oObject.computeBlob();
    oObject.computeShape();            
}


void Characterization::checkObjectDetails(Object& oObject)
{
    LOG4CXX_TRACE(logger, "Characterization.checkObjectDetails");
    
    // compute shapes of all object's components
    for (Body& oBody : oObject.getSubBodies())
    {
        //oBody.computeBlob(); // blobs computed during retinal vision
        oBody.computeShape();
    }

    // and compute object structure ...
    Structure2& oStructure = oObject.getStructure();
    // set object as structure reference
    oStructure.setReferenceBlob(oObject);    
    // get list of elements for the structure
    std::vector<Blob> listBlobs;
    for (Body& oBody : oObject.getSubBodies())
    {
        listBlobs.push_back(oBody);
    }        
    // compute structure
    oStructure.computeStructure(listBlobs);
    
    listBlobs.clear();
}
				 
}

