#ifndef __GOON_DATA_ROI_H
#define __GOON_DATA_ROI_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/data/base/Body.h"
#include "goon/data/motion/Motion.h"

namespace goon 
{
// This class represents a ROI (region of interest) which is the main output of the peripheral vision system.
// It extends from Body.
class ROI : public Body
{
private:
    int ID;
    int age;
    int stability;
    Motion oMotion;
    // matching info
    int touchedRegions;  // number of regions to which the ROI responds 
    int capturedRegion; // ID of captured region to update the ROI

public:    
    ROI();
    //~ROI();

    int getID() {return ID;};
    int getAge() {return age;};
    int getStability() {return stability;};
    void setID(int value) {ID = value;};
    void setAge(int value) {age = value;};
    void setStability(int value) {stability = value;};
    
    // matching info
    int getTouchedRegions() {return touchedRegions;};
    int getCapturedRegion() {return capturedRegion;};    
    void setTouchedRegions (int value) {touchedRegions = value;};
    void setCapturedRegion (int value) {capturedRegion = value;};
    void clearMatchingInfo();

    Motion& getMotion() {return oMotion;};
    void updateMotion(Move2D& oTransMove);
    // update blob part
    void updateBlob(Blob& oBlob);

    // support function to sort ROIs by ID
    static bool sortByID (const ROI& oROI1, const ROI& oROI2);        

    virtual std::string toString();    
    
    // returns short ROI description
    std::string shortDesc();    
};
}
   
  
#endif
