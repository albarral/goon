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

void Region::setMask(cv::Mat& mask)
{
    this->mask = mask.clone();    
}

// The given grid is cloned.
void Region::setGrid(cv::Mat& grid_samples)
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

void Region::cloneTo(Region& oRegion)
{
    oRegion = *this;    
    oRegion.setMask(mask);  // mask is cloned, not just assigned
    oRegion.setGrid(grid);     // grid is cloned, not just assigned
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
    createMask(mask, rect);
    setPos(w/2, h/2);
}
}
