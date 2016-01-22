/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/elements/Model.h"
	
namespace goon 
{
int Model::nextID = 1;

// constructor
Model::Model ()
{
    ID = nextID;
    Model::pushIDs();
}

void Model::addModelView(ModelView& modelView)
{
    listViews.push_back(modelView);
}
}
