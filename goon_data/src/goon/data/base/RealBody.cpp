/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/RealBody.h"

namespace goon 
{
RealBody::RealBody ()
{
    age = 0;
//    stability = 0;
}

void RealBody::setBody(Body& oBody)
{
    Body::operator =(oBody);    
}

void RealBody::updateMotion(int millis)
{
    oMotion.update(pos[0], pos[1], millis);
}

void RealBody::clear()
{
    Body::clear();

    age = 0;
    oMotion.clear();
}

std::string RealBody::toString()
{
    std::string desc = "RealBody [age = " + std::to_string(age) + 
//            ", stability = " + std::to_string(stability) + 
            "\n" + oMotion.toString() +
            "]" + 
            "\n" + Blob::toString() + 
            "\n" + Body::toString();
    return desc;
}

std::string RealBody::shortDesc()
{
    return ("RealBody: age = " + std::to_string(age) + 
 //           ", stability = " + std::to_string(stability) + 
            "\n" + oMotion.toString() +
            "\n" + Body::shortDesc());
}

}
