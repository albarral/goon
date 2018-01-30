/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/VisualMemory.h"

namespace goon 
{
// Constructor
VisualMemory::VisualMemory ()
{    
    ID = 0;    
}

// Destructor
VisualMemory::~VisualMemory ()
{
    clear();
}

void VisualMemory::clear()
{  
    listModels.clear();
    ID = 0;
}

void VisualMemory::addObjectModel(ObjectModel& oObjectModel)
{
    oObjectModel.setID(ID++);
    listModels.push_back(oObjectModel);
}  

std::string VisualMemory::toString()
{
    std::string desc = "VisualMemory:\n";
    std::vector<ObjectModel>::iterator it_model = listModels.begin();
    // walk list
    while (it_model != listModels.end())
    {            
        desc += it_model->toString() + "\n";
        it_model++;
    }
    return desc;
}

std::string VisualMemory::shortDesc()
{
    std::string desc = "VisualMemory:\n";
    std::vector<ObjectModel>::iterator it_model = listModels.begin();
    // walk list
    while (it_model != listModels.end())
    {            
        desc += it_model->shortDesc() + "\n";
        it_model++;
    }

    return desc;
}

}

