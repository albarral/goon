#ifndef __GOON_DATA_OBJECT_H
#define __GOON_DATA_OBJECT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "goon/data/base/Body.h"
#include "goon/features/structure/Structure.h"

namespace goon 
{
// This class represents an object, a body composed by other subbodies, all following a structure.
class Object : public Body
{
protected:
    int ID;
    std::vector<Body> listBodies;       // list of subbodies composing the object
    Structure oStructure;                   // object structure (distribution of subbodies)                    

public:    
    Object();
    ~Object();

    int getID() {return ID;};
    void setID(int value) {ID=value;};

    // set body part
    void setBody(Body& oBody);
    
    std::vector<Body>& getSubBodies() {return listBodies;};
    void addSubBody(Body& oBody);
    
    Structure& getStructure() {return oStructure;};   
    // compute object structure
    //void computeStructure();
    
    virtual void clear();
    
    virtual std::string toString();        
    virtual std::string shortDesc();    
};
}
   
  
#endif
