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
    bmatched = false;
}

bool ROI::sortByID (const ROI& oROI1, const ROI& oROI2)
{
    return (oROI1.ID < oROI2.ID);
}

std::string ROI::toString()
{
    std::string desc = "ROI [ID = " + std::to_string(ID) + RealBody::toString() + "]";
    return desc;
}

std::string ROI::shortDesc()
{
    return (std::to_string(ID) + RealBody::shortDesc());
}

}
