#ifndef __GOON_DATA_REALBODY_H
#define __GOON_DATA_REALBODY_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/features/Body.h"
#include "goon/features/motion/TransMotion.h"

namespace goon 
{
// This class represents a real body: a visual body that exists in the real world. 
// Therefore it has identity, motion and age.
class RealBody : public Body
{
protected:
    int ID;
    int age;
    TransMotion oMotion;

public:    
    RealBody();
    //~RealBody();

    // set body part
    void setBody(Body& oBody);

    int getID() {return ID;};
    void setID(int value) {ID = value;};
    int getAge() {return age;};
    void increaseAge() {age++;};
        
    TransMotion& getMotion() {return oMotion;};    
    void updateMotion(int millis);
    
    virtual void clear();
    
    virtual std::string toString();    
    virtual std::string shortDesc();    
};
}
   
  
#endif
