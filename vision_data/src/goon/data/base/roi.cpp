/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/roi.h"

namespace goon 
{
ROI::ROI ()
{
    ID = -1;
    age = 0;
}

ROI:: ~ROI ()
{
}

void ROI::setID(int value) {ID = value;}

void ROI::setAge(int value) {age = value;}

void ROI::setStability(int value) {stability = value;}

void ROI::updateMotion(features::Move2D& oTransMove)
{
    oMotion.update(oTransMove);
}

bool ROI::sortByID (const ROI& oROI1, const ROI& oROI2)
{
    return (oROI1.ID < oROI2.ID);
}

std::string ROI::shortDesc()
{
    return (std::to_string(ID) + ": age = " + std::to_string(age) + ", stability = " + std::to_string(stability) + "\n" + oMotion.toString());
}

}
