#ifndef __GOON_DATA_ROI_H
#define __GOON_DATA_ROI_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/data/base/Body.h"
#include "goon/data/motion/Motion.h"
#include "goon/data/motion/Move2D.h"

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
    Move2D oTransMove;
    Motion oMotion;
    // for matching 
    bool bmatched;      // for ROI-Region matching

public:    
    ROI();
    //~ROI();

    int getID() {return ID;};
    void setID(int value) {ID = value;};
    int getAge() {return age;};
    void increaseAge() {age++;};
    int getStability() {return stability;};
    void setStability(int value) {stability = value;};
    Move2D& getTransMove() {return oTransMove;}
    void setTransMove(Move2D& oTransMove) {this->oTransMove = oTransMove;};
    Motion& getMotion() {return oMotion;};
    void updateMotion(Move2D& oTransMove);
    void setMatched(bool bvalue) {bmatched = bvalue;};
    bool isMatched() {return bmatched;};
    
    // (deprecated) update blob part
    void updateBlob(Blob& oBlob);
    // set body part
    void setBody(Body& oBody);

    // support function to sort ROIs by ID
    static bool sortByID (const ROI& oROI1, const ROI& oROI2);        

    virtual std::string toString();    
    
    // returns short ROI description
    std::string shortDesc();    
};
}
   
  
#endif
