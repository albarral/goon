/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/blob.h"
#include "goon/features/color/rgb_color.h"
#include "goon/features/shape/shape.h"
#include "maty/math/distance.h"

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
    pos[0] = pos[1] = 0;
    covs[0] = covs[1] = covs[2] = 0.0;
    shapeFactor = 0.0;
    orientation = 0;    
    scale = 0.0;    
}

void Blob::merge(Blob& oBlob2)
{
    Shape::mergeEllipses (pos, covs, oBlob2.pos, oBlob2.covs, mass, oBlob2.mass);
    
    RGBColor::mergeValues(rgb_color, oBlob2.rgb_color, mass, oBlob2.mass);            
    hsv_color = RGBColor::toHSV (rgb_color);

    mass += oBlob2.mass;
    scale += oBlob2.scale;
    // to update shape factor & orientation the shape needs to be recomputed
}

std::string Blob::toString()
{
    std::string desc = "Blob [mass = " + std::to_string(mass) +
            ", pos = (" + std::to_string(pos[0]) + "," + std::to_string(pos[1]) + ")" +
            ", covs = (" + std::to_string((int)covs[0]) + "," + std::to_string((int)covs[1]) + "," + std::to_string((int)covs[2]) + ")" +
            ", shape_factor = " + std::to_string(shapeFactor) + ", orientation = " + std::to_string(orientation) + ", scale = " + std::to_string(scale) +
            ", rgb = (" + std::to_string((int)rgb_color[0]) + "," + std::to_string((int)rgb_color[1]) + "," + std::to_string((int)rgb_color[2]) + ")" +
            ", hsv = (" + std::to_string((int)hsv_color[0]) + "," + std::to_string((int)hsv_color[1]) + "," + std::to_string((int)hsv_color[2]) + ")]";
    return desc;
}

std::string Blob::shortDesc()
{
    std::string desc = "Blob [mass = " + std::to_string(mass) +
            ", pos = (" + std::to_string(pos[0]) + "," + std::to_string(pos[1]) + ")" +
            ", hsv = (" + std::to_string((int)hsv_color[0]) + "," + std::to_string((int)hsv_color[1]) + "," + std::to_string((int)hsv_color[2]) + ")]";
    return desc;
}
}
