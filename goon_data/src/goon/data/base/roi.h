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
    // for matching 
    bool bmatched;      // for ROI-Region matching

public:    
    ROI();
    //~ROI();

    void setMatched(bool bvalue) {bmatched = bvalue;};
    bool isMatched() {return bmatched;};
    
    virtual std::string toString();    
    virtual std::string shortDesc();    
};
}
   
  
#endif
