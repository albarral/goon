#ifndef __GOON_DATA_MODEL_H
#define __GOON_DATA_MODEL_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "goon/data/aux/Identity.h"
#include "goon/data/aux/Record.h"
#include "goon/data/elements/ModelView.h"

namespace goon 
{
// This class represents an object's model.
// It holds info about its appearance from different points of view, its existence and its history.
// Therefore if has a list of ModelViews (which inherit from VisualElement) and inherits from Identity and Record.
class Model : public Identity, public Record
{
private:
    static int nextID;  // shared by all models
    int ID;
    std::vector<ModelView> listViews;        
    
public:    
    Model();
     //~Model();

    static void pushIDs() {nextID++;};

    int getID() {return ID;}

    std::vector<ModelView>& getListViews() {return listViews;};
    void addModelView(ModelView& modelView);        
};
}
#endif
