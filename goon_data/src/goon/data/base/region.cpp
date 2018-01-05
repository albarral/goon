/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/region.h"
#include "goon/features/color/rgb_color.h"
	
namespace goon 
{
// constructor
Region::Region ()
{
    // blob constructor ... 
    type = Region::eREG_SIMPLE;
    bmerge = false;
    bmatched = false;
}

// copy constructor (needed for vectors)    
Region::Region(const Region& oRegion) : ColorBody(oRegion)       // base part constructor
{
    ID = oRegion.ID;
    type = oRegion.type;
    bmerge = oRegion.bmerge;
    bmatched = oRegion.bmatched;
    seed = oRegion.seed;
}  

// assignment operator
Region& Region::operator=(const Region& oRegion)
{
    ColorBody::operator=(oRegion); // base part assignment

    ID = oRegion.ID;
    type = oRegion.type;
    bmerge = oRegion.bmerge;
    bmatched = oRegion.bmatched;
    seed = oRegion.seed;
    return *this;    
}
    
bool Region::sortBySize(const Region& oRegion1, const Region& oRegion2) 
{
    return (oRegion1.mass < oRegion2.mass);
}

std::string Region::toString()
{
    std::string desc = "Region [ID = " + std::to_string(ID) +
            ", type = " + getTypeName() +
            ", mask = " + std::to_string(getMask().cols) + "x" + std::to_string(getMask().rows) +
            ", merge = " + (bmerge ? "1":"0") + 
            "]" + 
            "\n" + Body::toString();
    return desc;
}

std::string Region::shortDesc()
{
    return (std::to_string(ID) + ": " + std::to_string(mass) + " " + 
            std::to_string(getMask().cols) + "x" + std::to_string(getMask().rows) + 
             " \t\t hsv = (" + std::to_string((int)hsv_color[0]) + "," + std::to_string((int)hsv_color[1]) + "," + std::to_string((int)hsv_color[2]) + ") - " + getTypeName() );
}

std::string Region::getTypeName()
{
    std::string name;
    switch (type)
    {
        case Region::eREG_SIMPLE:
            name = "simple";
            break;
        case Region::eREG_MERGED:
            name = "merged";
            break;
        case Region::eREG_COLLECTION:
            name = "collection";
            break;
    }
    return name;
}
}
