/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/
  
#include "goon/cortex/analysis/characterization.h"

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

    // resize object's structure to manage all components
    Structure& oStructure = oObject.getStructure();
    oStructure.resize(oObject.getSubBodies().size());
    
    // compute local structure of all object's components
    std::vector<cv::Vec4f> listNeighbours;
    int index = 0;
    for (Body& oBody : oObject.getSubBodies())
    {
        listNeighbours = characterizeLocalStructure(oBody, oObject.getSubBodies());
        // and add it to global structure
        oStructure.setNeighbours(index, listNeighbours); 
        index++;
    }    
}
				 

// This function characterizes the neighborhood of a given body
std::vector<cv::Vec4f> Characterization::characterizeLocalStructure(Body& oBody, std::vector<Body>& listBodies)
{
    LOG4CXX_TRACE(logger, "Characterization.characterizeLocalStructure");
    
    std::vector<cv::Vec4f> listSpatialRelations;
    // compute spatial relations from given body to rest of bodies
    int index = 0;
    for (Body& oBody2 : listBodies)
    {
        // CAUTION, avoid computing spatial relation to itself
        cv::Vec3f spacialRelation = oBody.computeSpatialRelation2Blob(oBody2);
        listSpatialRelations.push_back(cv::Vec4f(index, spacialRelation[0], spacialRelation[1], spacialRelation[2]));
        index++;
    }
    
    return listSpatialRelations;
}
}

