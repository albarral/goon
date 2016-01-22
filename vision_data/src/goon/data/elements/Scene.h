#ifndef __GOON_DATA_SCENE_H
#define __GOON_DATA_SCENE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <opencv2/core/core.hpp>

#include "goon/data/elements/Object.h"

namespace goon 
{
// This class represents a scene.
// It holds info about its objects and their distribution in space.
class Scene
{
private:
    std::vector<Object> listObjects;        
    cv::Mat mat_dist;           // spatial distribution of objects
    
public:    
    Scene();
     //~Scene();

    std::vector<Object>& getListViews() {return listObjects;};
    void addObject(Object& object, cv::Vec2f pos, float scale);        
    
    cv::Mat& getMatDistribution() {return mat_dist;}
};
}
#endif
