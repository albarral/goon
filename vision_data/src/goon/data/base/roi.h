#ifndef __GOON_DATA_ROI_H
#define __GOON_DATA_ROI_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/blob.h"
#include "goon/features/motion/Motion.h"

namespace goon 
{
// This class represents a ROI (region of interest) which is the main output of the peripheral vision system.
// It extends from Blob.
class ROI : public Blob
{
    private:
        int ID;
        int age;
        int stability;
        features::Motion oMotion;

public:
        ROI();
        ~ROI();
        
        int getID() {return ID;};
        int getAge() {return age;};
        int getStability() {return stability;};
                
        void setID (int value);
        void setAge (int value);
        void setStability (int value);

        features::Motion& getMotion() {return oMotion;};
        void updateMotion(features::Move2D& oTransMove);
        
        // support function to sort ROIs by ID
        static bool sortByID (const ROI& oROI1, const ROI& oROI2);        
};
}
   
  
#endif
