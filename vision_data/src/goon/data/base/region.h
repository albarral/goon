#ifndef __GOON_DATA_REGION_H
#define __GOON_DATA_REGION_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"

#include "goon/data/base/Body.h"

namespace goon 
{
// This class represents a region, the basic element in the retinal vision process.
// It extends from Body.
class Region : public Body
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
    cv::Mat grid;                    // grid used for merging purpose
    bool bmerge;                   // flag indicating that region is to be merged
    bool bcaptured;             // indicates region was captured by a ROI
    // for degug ...
    cv::Point seed;                 // first point of the region 

public:
    Region();
    //~Region();
    
    // copy constructor (needed for grid)
    Region(const Region& oRegion);  
    // assignment operator (needed for grid)
    Region& operator=(const Region& oRegion);
        
    int getID() {return ID;}
    int getType() {return type;}
    cv::Mat& getGrid() {return grid;}
    bool is2Merge() {return bmerge;}
    bool isCaptured() {return bcaptured;}
    cv::Point& getSeed() {return seed;}
    
    void setID(int value) {ID = value;}
    void setType(int value) {type = value;}
    void setMerge(bool bvalue) {bmerge = bvalue;}
    void setCaptured(bool bvalue) {bcaptured = bvalue;}
    void setSeed(cv::Point& seed_point) {seed = seed_point;}
    
    // initializes mask and grid
    void init();

    // clears the region's features (mask, grid, window)
    //void clear();

    // sets the region's grid (new cloned matrix)
    void setGrid (const cv::Mat& grid_samples);
        
    // support function to sort regions by ID
    static bool sortBySize (const Region& oRegion1, const Region& oRegion2);    
        
    // creates a dummy red rectangular region of size 200 x 100
    void createDummy();

    // returns all region values in string form
    virtual std::string toString();    
    // returns short region description
    std::string shortDesc();    
    // returns name of region type
    std::string getTypeName();  
 };
 }

#endif
