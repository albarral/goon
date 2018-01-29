/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/cortex/ObjectModel.h"

namespace goon 
{
ObjectModel::ObjectModel ()
{
    clear();
}

ObjectModel::~ObjectModel()
{
    listModels.clear();
}

void ObjectModel::addSubModel(Model& oModel)
{
    listModels.push_back(oModel);
}

//void ObjectModel::computeStructure()
//{
//    // TO DO    
//}

void ObjectModel::clear()
{
    Model::clear();
    
    listModels.clear();
    oStructure.clear();
}

std::string ObjectModel::toString()
{
    std::string desc = "ObjectModel [" + Model::toString() +
            "\n submodels " + std::to_string(listModels.size()) + ":\n"; 
    // add submodels descriptions
    for (Model& oModel : listModels)
    {
        desc += oModel.toString() + "\n";
    }    
    return desc;
}

std::string ObjectModel::shortDesc()
{
    std::string desc = "ObjectModel [" + Model::shortDesc() +
            "\n submodels " + std::to_string(listModels.size()) + ":\n"; 
    // add submodels descriptions
    for (Model& oModel : listModels)
    {
        desc += oModel.shortDesc() + "\n";
    }    
    return desc;
}

}
