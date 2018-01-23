#ifndef __GOON_DATA_REGION_H
#define __GOON_DATA_REGION_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include "opencv2/core/core.hpp"

#include "goon/data/base/ColorBody.h"

namespace goon 
{
// This class represents a region, the basic element in the retinal vision process.
// It extends from ColorBody.
class Region : public ColorBody
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
    bool bmerge;                   // flag indicating that region is to be merged
    // for matching 
    bool bmatched;              // for ROI-Region matching
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
    void setID(int value) {ID = value;}
    int getType() {return type;}
    void setType(int value) {type = value;}
    bool is2Merge() {return bmerge;}
    void setMerge(bool bvalue) {bmerge = bvalue;}
    bool isMatched() {return bmatched;};
    void setMatched(bool bvalue) {bmatched = bvalue;};
    cv::Point& getSeed() {return seed;}
    void setSeed(cv::Point& seed_point) {seed = seed_point;}
    
    bool isSimple() {return (type==eREG_SIMPLE);};
    bool isMerged() {return (type==eREG_MERGED);};
    bool isCollection() {return (type==eREG_COLLECTION);};

    // support function to sort regions by ID
    static bool sortBySize (const Region& oRegion1, const Region& oRegion2);    
        
    virtual std::string toString();    
    virtual std::string shortDesc();    

    // returns name of region type
    std::string getTypeName();  
 };
 }

#endif
