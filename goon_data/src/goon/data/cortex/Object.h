#ifndef __GOON_DATA_OBJECT_H
#define __GOON_DATA_OBJECT_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "goon/features/Body.h"
#include "goon/features/structure/Structure2.h"

namespace goon 
{
// This class represents an object, a body composed by other subbodies, all following a structure.
class Object : public Body
{
protected:
    int ID;
    std::vector<Body> listBodies;       // list of subbodies composing the object
    Structure2 oStructure;                   // object structure (distribution of subbodies)                    

public:    
    Object();
    ~Object();

    int getID() {return ID;};
    void setID(int value) {ID=value;};

    // set body part
    void setBody(Body& oBody);
    
    std::vector<Body>& getSubBodies() {return listBodies;};
    void addSubBody(Body& oBody);
    
    Structure2& getStructure() {return oStructure;};   
    
    virtual void clear();
    
    virtual std::string toString();        
    virtual std::string shortDesc();    
};
}
   
  
#endif
