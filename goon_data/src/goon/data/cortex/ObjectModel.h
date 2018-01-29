#ifndef __GOON_DATA_OBJECTMODEL_H
#define __GOON_DATA_OBJECTMODEL_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "goon/data/cortex/Model.h"
#include "goon/features/structure/Structure.h"

namespace goon 
{
// Class used to represent an object model, the symbolic representation of a visual object.    
// An object model is itself a model composed by submodels distributed in a determined structure.
class ObjectModel : public Model
{
private:
    std::vector<Model> listModels;     // list of submodels composing the object
    Structure oStructure;                   // object structure (distribution of submodels)                    

public:    
    ObjectModel();
    ~ObjectModel();

    std::vector<Model>& getSubModels() {return listModels;};
    void addSubModel(Model& oModel);
    
    Structure& getStructure() {return oStructure;};   
    // compute object structure
    //void computeStructure();
    
    void clear();
    
    virtual std::string toString();        
    virtual std::string shortDesc();    
};
}
   
  
#endif
