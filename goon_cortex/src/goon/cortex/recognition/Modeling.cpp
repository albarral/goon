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
    refWidth = 100;
    refMass = 100;
}

//Modeling::~Modeling ()
//{
//}


void Modeling::modelObject(Object& oObject, ObjectModel& oObjectModel)
{
    LOG4CXX_TRACE(logger, "Modeling.modelObject");
    
    // first clear the model
    oObjectModel.clear();
    
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
    cv::Point pos2 = (oBody.getPos() - trans) * scaling;
    cv::Rect window2 = oBody.getWindow() - trans;
    window2.width *= scaling;    
    window2.height *= scaling;    
    // normalization
    int mass2 = oBody.getMass() * normalization;
    
    // assign color blob part of body to model
    ColorBlob& oColorBlob1 = oBody;
    ColorBlob& oColorBlob2 = oModel;
    oColorBlob2 = oColorBlob1;
    
    // assign new position, window & mass
    oModel.setPos(pos2.x, pos2.y);
    oModel.setWindow(window2);    
    oModel.setMass(mass2);    
} 

}
