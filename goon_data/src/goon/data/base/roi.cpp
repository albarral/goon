/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/roi.h"

namespace goon 
{
ROI::ROI ()
{
    bmatched = false;
}

std::string ROI::toString()
{
    std::string desc = "ROI [" + RealBody::toString() + "]";
    return desc;
}

std::string ROI::shortDesc()
{
    std::string desc = "ROI [" + RealBody::shortDesc() + "]";
    return desc;
}

}
