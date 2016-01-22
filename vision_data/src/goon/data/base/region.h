#ifndef __GOON_DATA_REGION_H
#define __GOON_DATA_REGION_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#include "goon/data/base/blob.h"

namespace goon 
{
// This class represents a region, the basic element in the retinal vision process.
// It extends from Blob.
class Region : public Blob
{
 public:
    enum eTypes
    {
         eREG_SIMPLE, 
         eREG_MERGED, 
         eREG_COLLECTION
    };	

private:
    int ID;
    int type;
    cv::Mat mask;                  // roi mask storing the region's shape
    cv::Mat grid;                    // grid used for merging purpose
    bool bmerge;                   // flag indicating that region is to be merged
    // for degug ...
    cv::Point seed;                 // first point of the region 

public:
    Region ();
    //~Region();
        
    int getID() {return ID;}
    int getType() {return type;}
    cv::Mat& getMask() {return mask;}
    cv::Mat& getGrid() {return grid;}
    int is2Merge() {return bmerge;}
    cv::Point& getSeed() {return seed;}
    
    void setID (int value);
    void setType (int value);
    void setMerge(bool bvalue);
    void setSeed(cv::Point& seed_point);
    
    // initializes mask and grid
    void init();

    // clears the region's features (mask, grid, window)
    void clear();

    // sets the region's mask and window (cloned matrix)
    void setMask (cv::Mat& rmask, cv::Rect& rwindow);

    // sets the region's grid (cloned matrix)
    void setGrid (cv::Mat& grid_samples);
        
    // grows this region by absorbing a new one 
    void growRegion(Region& oRegion2);

    // support function to sort regions by ID
    static bool sortBySize (const Region& oRegion1, const Region& oRegion2);    
 };
 }

#endif
