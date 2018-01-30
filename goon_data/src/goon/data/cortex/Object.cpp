/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/cortex/Object.h"

namespace goon 
{
Object::Object ()
{
    ID = 0;
}

Object::~Object()
{
    listBodies.clear();
}

void Object::setBody(Body& oBody)
{
    Body::operator =(oBody);    
}

void Object::addSubBody(Body& oBody)
{
    listBodies.push_back(oBody);
}

void Object::clear()
{
    Body::clear();
    
    listBodies.clear();
    oStructure.clear();
}

std::string Object::toString()
{
    std::string desc = "Object [ID = " + std::to_string(ID) + " " + Body::toString() + 
            "\n subbodies " + std::to_string(listBodies.size()) + ":\n"; 
    // add subbodies descriptions
    for (Body& oBody : listBodies)
    {
        desc += oBody.toString() + "\n";
    }    
    return desc;
}

std::string Object::shortDesc()
{
    std::string desc = "Object [ID = " + std::to_string(ID) + " " + Body::shortDesc() + 
            "\n subbodies " + std::to_string(listBodies.size()) + ":\n"; 
    // add subbodies descriptions
    for (Body& oBody : listBodies)
    {
        desc += oBody.shortDesc() + "\n";
    }    
    return desc;
}

}
