#ifndef __GOON_DATA_OBJECT_H
#define __GOON_DATA_OBJECT_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/aux/VisualElement.h"
#include "goon/data/aux/Body.h"
#include "goon/data/aux/Identity.h"

namespace goon 
{
// This class represents a visual object.
// It holds info about its appearance, its physical presence and its existence.
// Therefore it inherits from VisualElement, Body and Identity.
class Object : public VisualElement, public Body, public Identity
{
private:
    int ID;
    
public:    
    Object();
     //~Object();

    int getID() {return ID;};       
    void setID (int value) {ID = value;};                    
    
};
}
#endif
