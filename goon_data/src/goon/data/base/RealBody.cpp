/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/RealBody.h"

namespace goon 
{
RealBody::RealBody ()
{
    ID = -1;
    age = 0;
}

void RealBody::setBody(Body& oBody)
{
    Body::operator =(oBody);    
}

void RealBody::updateMotion(int millis)
{
    oMotion.update(pos.x, pos.y, millis);
}

void RealBody::clear()
{
    Body::clear();

    ID = -1;
    age = 0;
    oMotion.clear();
}

std::string RealBody::toString()
{
    std::string desc = "RealBody [ID = " + std::to_string(ID) + ", age = " + std::to_string(age) + 
            ", " + oMotion.toString() +
            "\n" + Body::toString();
    return desc;
}

std::string RealBody::shortDesc()
{
    return ("RealBody [ID = " + std::to_string(ID) + ", age = " + std::to_string(age) + 
            ", " + oMotion.shortDesc() +
            ", " + Body::shortDesc());
}

}
