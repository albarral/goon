/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/cortex/Scene.h"

namespace goon 
{
Scene::Scene ()
{
}

Scene::~Scene()
{
    listObjects.clear();
}

void Scene::addObject(Object& oObject)
{
    listObjects.push_back(oObject);
}

//void Scene::computeStructure()
//{
//    // TO DO    
//}

void Scene::clear()
{    
    listObjects.clear();
    
    oStructure.clear();    
}

std::string Scene::toString()
{
    std::string desc = "Scene [objects " + std::to_string(listObjects.size()) + ":\n"; 
    // add objects descriptions
    for (Object& oObject : listObjects)
    {
        desc += oObject.toString() + "\n";
    }    
    return desc;
}

std::string Scene::shortDesc()
{
    std::string desc = "Scene [objects " + std::to_string(listObjects.size()) + ":\n"; 
    // add objects descriptions
    for (Object& oObject : listObjects)
    {
        desc += oObject.shortDesc() + "\n";
    }    
    return desc;
}

}
