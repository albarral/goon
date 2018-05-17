/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/ColorBlob.h"
#include "goon/features/color/rgb_color.h"

namespace goon 
{
// constructor
ColorBlob::ColorBlob ()
{
}

void ColorBlob::merge(ColorBlob& oColorBlob2)
{
    Blob::merge(oColorBlob2);

    // merge colors
    RGBColor::mergeValues(rgb_color, oColorBlob2.rgb_color, mass, oColorBlob2.mass);            
    hsv_color = RGBColor::toHSV (rgb_color);
}

std::string ColorBlob::toString()
{
    std::string desc = "ColorBlob [ rgb = (" + std::to_string((int)rgb_color[0]) + "," + std::to_string((int)rgb_color[1]) + "," + std::to_string((int)rgb_color[2]) + ")" +
            ", hsv = (" + std::to_string((int)hsv_color[0]) + "," + std::to_string((int)hsv_color[1]) + "," + std::to_string((int)hsv_color[2]) + ") " +
                Blob::toString() + "]";
    return desc;
}

std::string ColorBlob::shortDesc()
{
    std::string desc = "ColorBlob [ hsv = (" + std::to_string((int)hsv_color[0]) + "," + std::to_string((int)hsv_color[1]) + "," + std::to_string((int)hsv_color[2]) + ") " +
                Blob::shortDesc() + "]";
    return desc;
}
}
