/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/cortex/recognition/Recall.h"

namespace goon 
{
// Constructor
Recall::Recall ()
{    
    ID = 0;    
}

// Destructor
Recall::~Recall ()
{
    clear();
}

void Recall::clear()
{  
    listRecalledModels.clear();
    listNewModels.clear();
    ID = 0;
}

void Recall::addNewModel(ObjectModel& oObjectModel)
{
    oObjectModel.setID(ID++);
    listNewModels.push_back(oObjectModel);
}  

void Recall::fetchModels(ObjectModel& oObjectModel, int start)
{
    listRecalledModels.clear();
    
    std::vector<ObjectModel>& listModels = oVisualMemory.getListModels();
    // fetch 20 
    int end = start + 20;
    int top = listModels.size();
    std::vector<ObjectModel>::iterator it_model = listRecalledModels.begin();
    // walk list
    for (int i=start; i<end; i++) 
    {            
        if (i < top)
        {
            ObjectModel& oRecalledModel = listModels.at(i);
            listRecalledModels.push_back(oRecalledModel);
        }
        else
            break;
    }    
}

void Recall::fixModels()
{
    // push all new models to visual memory
    std::vector<ObjectModel>& listModels = oVisualMemory.getListModels();
    listModels.insert(listModels.end(), listNewModels.begin(), listNewModels.end());    
}


std::string Recall::toString()
{
    std::string desc = "Recall:\n";
    desc += "recalled models ...\n";
    std::vector<ObjectModel>::iterator it_model = listRecalledModels.begin();
    // walk list
    while (it_model != listRecalledModels.end())
    {            
        desc += it_model->toString() + "\n";
        it_model++;
    }
    
    desc += "new models ...\n";
    it_model = listNewModels.begin();
    // walk list
    while (it_model != listNewModels.end())
    {            
        desc += it_model->toString() + "\n";
        it_model++;
    }
    return desc;
}

std::string Recall::shortDesc()
{
    std::string desc = "Recall:\n";
    desc += "recalled models ...\n";
    std::vector<ObjectModel>::iterator it_model = listRecalledModels.begin();
    // walk list
    while (it_model != listRecalledModels.end())
    {            
        desc += it_model->shortDesc() + "\n";
        it_model++;
    }
    
    desc += "new models ...\n";
    it_model = listNewModels.begin();
    // walk list
    while (it_model != listNewModels.end())
    {            
        desc += it_model->shortDesc() + "\n";
        it_model++;
    }
    return desc;
}

}

