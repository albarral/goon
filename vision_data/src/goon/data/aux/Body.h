#ifndef __GOON_DATA_BODY_H
#define __GOON_DATA_BODY_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

//#include "goon/data/aux/vPosition.h"
#include "goon/data/aux/vMotion.h"

namespace goon 
{
// This class represents a object's physical presence.
// It holds info such as: position, scale, orientation, motion and trajectory.
class Body 
{
protected:
    //vPosition pos;
    float scale;
    int orientation;   
    vMotion motion;
    
public:
    Body();
    //~Body();
    
    //vPosition& getPosition() {return pos;}

    float getScale() {return scale;}    
    void setScale (float value) {scale = value;};

    int getOrientation() {return orientation;};       
    void setOrientation (int value) {orientation = value;};                    

    vMotion& getMotion() {return motion;};     
 };
}
#endif
