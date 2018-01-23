#ifndef __GOON_DATA_SCENE_H
#define __GOON_DATA_SCENE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "goon/data/cortex/Object.h"
#include "goon/features/structure/Structure.h"

namespace goon 
{
// This class represents a scene, a group of objects all following a structure.
class Scene 
{
private:
    std::vector<Object> listObjects;       // list of objects composing the scene
    Structure oStructure;                   // scene structure (distribution of objects)                    

public:    
    Scene();
    ~Scene();
    
    std::vector<Object>& getObjects() {return listObjects;};
    void addObject(Object& oObject);
    
    Structure& getStructure() {return oStructure;};   
    // compute scene structure
    //void computeStructure();
    
    void clear();
    
    virtual std::string toString();        
    virtual std::string shortDesc();    
};
}
   
  
#endif
