/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "goon/cortex/recognition/Modeling.h"
							
using namespace log4cxx;

namespace goon
{
LoggerPtr Modeling::logger(Logger::getLogger("goon.cortex.recognition"));


// Constructor
Modeling::Modeling()
{
}

//Modeling::~Modeling ()
//{
//}


void Modeling::modelObject(Object& oObject, ObjectModel& oObjectModel)
{
    LOG4CXX_TRACE(logger, "Modeling.modelObject");
    
    cv::Rect& window = oObject.getWindow();
    trans.x = window.x;
    trans.y = window.y;    
    scaling = (float)refWidth/window.width;    
    normalization = (float)refMass/oObject.getMass();
    
    modelBody(oObject, oObjectModel);
    
    for (Body& oBody : oObject.getSubBodies())
    {
        Model oModel;
        modelBody(oBody, oModel);
        
        oObjectModel.addSubModel(oModel);
    }
}


void Modeling::modelBody(Body& oBody, Model& oModel)
{
    LOG4CXX_TRACE(logger, "Modeling.modelBody");

    // TO DO ..
} 

}
