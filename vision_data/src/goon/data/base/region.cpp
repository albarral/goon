/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/region.h"
#include "goon/utils/rgb_color.h"
	
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
Region::Region(const Region& oRegion) : Body(oRegion)       // base part constructor
{
    ID = oRegion.ID;
    type = oRegion.type;
    setGrid(oRegion.grid);   // grid is cloned, not just assigned
    bmerge = oRegion.bmerge;
    bmatched = oRegion.bmatched;
    seed = oRegion.seed;
}  

// assignment operator
Region& Region::operator=(const Region& oRegion)
{
    Body::operator=(oRegion); // base part assignment

    ID = oRegion.ID;
    type = oRegion.type;
    setGrid(oRegion.grid);   // grid is cloned, not just assigned
    bmerge = oRegion.bmerge;
    bmatched = oRegion.bmatched;
    seed = oRegion.seed;
    return *this;    
}
    
// The given grid is cloned.
void Region::setGrid(const cv::Mat& grid_samples)
{
    grid = grid_samples.clone();
}

bool Region::sortBySize(const Region& oRegion1, const Region& oRegion2) 
{
    return (oRegion1.mass < oRegion2.mass);
}

void Region::createDummy()
{
    // red
    cv::Vec3f color = {255.0, 0.0, 0.0};
    // create rectangular region w x h
    int w = 200;
    int h = 100;    
    cv::Mat mask = cv::Mat::ones(h, w, CV_8UC1);
    cv::Rect rect = cv::Rect(0, 0, w,h);
    
    setRGB(color);
    setMaskAndWindow(mask, rect);
    setPos(w/2, h/2);
}

std::string Region::toString()
{
    std::string desc = "Region [ID = " + std::to_string(ID) +
            ", type = " + getTypeName() +
            ", mask = " + std::to_string(getMask().cols) + "x" + std::to_string(getMask().rows) +
            ", grid = " + std::to_string(grid.cols) + "x" + std::to_string(grid.rows) +
            ", merge = " + (bmerge ? "1":"0") + 
            "]" + 
            "\n" + Blob::toString() + 
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
