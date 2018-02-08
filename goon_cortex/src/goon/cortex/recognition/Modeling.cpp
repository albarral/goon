/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "goon/cortex/recognition/Modeling.h"
#include "goon/features/ColorBlob.h"
							
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
    
    // compute the translation, scaling and normalization to be applied
    cv::Rect& window = oObject.getWindow();
    trans.x = window.x;
    trans.y = window.y;    
    scaling = (float)refWidth/window.width;    
    normalization = (float)refMass/oObject.getMass();
    
    // model the object's global body
    modelBody(oObject, oObjectModel);
    
    // model the object subbodies, adding them to the object model
    int ID = 0;
    for (Body& oBody : oObject.getSubBodies())
    {
        Model oModel;
        modelBody(oBody, oModel);
        
        // assign an ID to each submodel
        oModel.setID(ID++);
        oObjectModel.addSubModel(oModel);
    }
}


void Modeling::modelBody(Body& oBody, Model& oModel)
{
    LOG4CXX_TRACE(logger, "Modeling.modelBody");

    // translation & scaling
    cv::Point newPos = (oBody.getPos() - trans) * scaling;
    cv::Rect newWindow = oBody.getWindow() - trans;
    newWindow.width *= scaling;    
    newWindow.height *= scaling;    
    // normalization
    int newMass = oBody.getMass() * normalization;
    
    // assign color blob part
    //oModel = (ColorBlob)oBody;
    
    // assign new position, window & mass
    oModel.setPos(newPos.x, newPos.y);
    oModel.setWindow(newWindow);    
    oModel.setMass(newMass);    
} 

}
