/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/elements/Scene.h"
	
namespace goon 
{
// constructor
Scene::Scene ()
{
}

void Scene::addObject(Object& object, cv::Vec2f pos, float scale)
{
    listObjects.push_back(object);

    cv::Vec3f dist = {pos[0], pos[1], scale};

    mat_dist.push_back(dist);
}
}
