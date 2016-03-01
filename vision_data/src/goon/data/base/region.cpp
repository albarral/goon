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
}

// copy constructor (needed for vectors)    
Region::Region(const Region& oRegion) : Blob(oRegion) // dispatch to base copy constructor
{
    ID = oRegion.ID;
    type = oRegion.type;
    setMask(oRegion.mask); // mask is cloned, not just assigned
    setGrid(oRegion.grid);   // grid is cloned, not just assigned
    bmerge = oRegion.bmerge;
    seed = oRegion.seed;
}  

// assignment operator
Region& Region::operator=(const Region& oRegion)
{
    Blob::operator=(oRegion);   // blob part copied
    ID = oRegion.ID;
    type = oRegion.type;
    setMask(oRegion.mask); // mask is cloned, not just assigned
    setGrid(oRegion.grid);   // grid is cloned, not just assigned
    bmerge = oRegion.bmerge;
    seed = oRegion.seed;
    return *this;    
}
    
void Region::setID(int value) {ID = value;}
void Region::setType(int value) {type = value;}
void Region::setMerge (bool bvalue) {bmerge = bvalue;}
void Region::setSeed(cv::Point& seed_point) {seed = seed_point;}

void Region::clear()
{
    if (mass > 0)
    {
        mass = 0;
        window = cv::Rect (0,0,0,0);
        type = Region::eREG_SIMPLE;
        // mask and grid are newly set on segmentation
        bmerge = false;
    }    
}

// The given mask is roied and cloned.
void Region::createMask(cv::Mat& mask, cv::Rect& window)
{
    cv::Mat roiMask = mask(window);   
    setMask(roiMask);
    
    // the region's window is also set
    setWindow(window);
}

void Region::setMask(const cv::Mat& mask)
{
    this->mask = mask.clone();    
}

// The given grid is cloned.
void Region::setGrid(const cv::Mat& grid_samples)
{
    grid = grid_samples.clone();
}

void Region::growRegion(Region& oRegion2)
{
    // create a new window & mask
    cv::Rect new_window = window | oRegion2.window;    
    cv::Point origin (new_window.x, new_window.y);    
    cv::Mat new_mask = cv::Mat::zeros(new_window.width, new_window.height, CV_8UC1);

    // set rois to the new mask
    cv::Mat roi1 = new_mask(window - origin);
    cv::Mat roi2 = new_mask(oRegion2.window - origin);

    // join both region masks into the new mask
    mask.copyTo(roi1);
    roi2 = roi2 + oRegion2.getMask();

    // store new values
    mask = new_mask;
    window = new_window;
    // merge colors
    RGBColor::mergeValues(rgb_color, oRegion2.rgb_color, mass, oRegion2.mass);            
    // add mass
    mass += oRegion2.mass;
}

bool Region::sortBySize(const Region& oRegion1, const Region& oRegion2) 
{
    return (oRegion1.mass < oRegion2.mass);
}

//void Region::cloneTo(Region& oRegion)
//{
//    oRegion = *this;    
//    oRegion.setMask(mask);  // mask is cloned, not just assigned
//    oRegion.setGrid(grid);     // grid is cloned, not just assigned
//}

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
    createMask(mask, rect);
    setPos(w/2, h/2);
}

std::string Region::toString()
{
    std::string desc = "Region [ID = " + std::to_string(ID) +
            ", type = " + getTypeName() +
            ", mask = " + std::to_string(mask.cols) + "x" + std::to_string(mask.rows) +
            ", grid = " + std::to_string(grid.cols) + "x" + std::to_string(grid.rows) +
            ", merge = " + (bmerge ? "1":"0") + 
            "]" + "\n" +
            Blob::toString();
    return desc;
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
