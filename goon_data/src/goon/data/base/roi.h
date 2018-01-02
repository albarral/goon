#ifndef __GOON_DATA_ROI_H
#define __GOON_DATA_ROI_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/data/base/RealBody.h"

namespace goon 
{
// This class represents a ROI (region of interest) which is the main output of the peripheral vision system.
class ROI : public RealBody
{
private:
    int ID;
    // for matching 
    bool bmatched;      // for ROI-Region matching

public:    
    ROI();
    //~ROI();

    int getID() {return ID;};
    void setID(int value) {ID = value;};
    void setMatched(bool bvalue) {bmatched = bvalue;};
    bool isMatched() {return bmatched;};
    
    // support function to sort ROIs by ID
    static bool sortByID (const ROI& oROI1, const ROI& oROI2);        

    virtual std::string toString();    
    
    // returns short ROI description
    virtual std::string shortDesc();    
};
}
   
  
#endif
