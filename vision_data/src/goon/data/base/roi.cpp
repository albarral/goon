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
    clearMatchingInfo();
}


void ROI::clearMatchingInfo()
{
    touchedRegions = 0;
    capturedRegion = -1;    
}


void ROI::updateMotion(Move2D& oTransMove)
{
    oMotion.update(oTransMove);
}

void ROI::updateBlob(Blob& oBlob)
{
    Blob::operator=(oBlob);    
}


bool ROI::sortByID (const ROI& oROI1, const ROI& oROI2)
{
    return (oROI1.ID < oROI2.ID);
}

std::string ROI::toString()
{
    std::string desc = "ROI [ID = " + std::to_string(ID) +
            ": age = " + std::to_string(age) + 
            ", stability = " + std::to_string(stability) + 
            "\n" + oMotion.toString() +
            "]" + 
            "\n" + Blob::toString() + 
            "\n" + Body::toString();
    return desc;
}

std::string ROI::shortDesc()
{
    return (std::to_string(ID) + 
            ": age = " + std::to_string(age) + 
            ", stability = " + std::to_string(stability) + 
            "\n" + oMotion.toString());
}

}
