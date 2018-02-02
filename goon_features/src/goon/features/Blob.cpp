/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/Blob.h"
#include "goon/features/shape/shape.h"

namespace goon 
{
// constructor
Blob::Blob ()
{
    clear();
}

void Blob::clear()
{
    mass = 0;
    pos.x = pos.y = 0;
    covs[0] = covs[1] = covs[2] = 0.0;
    shapeFactor = 0.0;
    orientation = 0;    
}

void Blob::merge(Blob& oBlob2)
{
    Shape::mergeEllipses(pos, covs, oBlob2.pos, oBlob2.covs, mass, oBlob2.mass);

    mass += oBlob2.mass;
    // to update shape factor & orientation the shape needs to be recomputed
}

std::string Blob::toString()
{
    std::string desc = "Blob [mass = " + std::to_string(mass) +
            ", pos = (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + 
            "), covs = (" + std::to_string((int)covs[0]) + "," + std::to_string((int)covs[1]) + "," + std::to_string((int)covs[2]) + 
            "), shape_factor = " + std::to_string(shapeFactor) + ", orientation = " + std::to_string(orientation) + "]";
    return desc;
}

std::string Blob::shortDesc()
{
    std::string desc = "Blob [mass = " + std::to_string(mass) +
            ", pos = (" + std::to_string(pos.x) + "," + std::to_string(pos.y) + ")]";
    return desc;
}
}
