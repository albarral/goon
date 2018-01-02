#ifndef __GOON_DATA_REALBODY_H
#define __GOON_DATA_REALBODY_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/data/base/Body.h"
#include "goon/data/base/TransMotion.h"

namespace goon 
{
// This class represents a real body: a visual body that has exists in the real world. 
// Therefore it has a motion and a historical existence.
class RealBody : public Body
{
protected:
    int age;
    int stability;
    TransMotion oMotion;

public:    
    RealBody();
    //~RealBody();

    // set body part
    void setBody(Body& oBody);

    int getAge() {return age;};
    void increaseAge() {age++;};
    
    int getStability() {return stability;};
    void setStability(int value) {stability = value;};
    
    TransMotion& getMotion() {return oMotion;};    
    void updateMotion(int millis);
    
    virtual std::string toString();    
    
    // returns short RealBody description
    std::string shortDesc();    
};
}
   
  
#endif
