#ifndef __GOON_DATA_ROI_H
#define __GOON_DATA_ROI_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/blob.h"
#include "goon/data/base/motion.h"

namespace goon 
{
// This class represents a ROI (region of interest) which is the main output of the peripheral vision system.
// It extends from Blob and Motion classes.
//class ROI : public Blob, public Motion
class ROI : public Blob
{
    private:
        int ID;
        int age;
        int stability;
        int speed[2];   // (vx, vy) in pixels/second

public:
        ROI();
        ~ROI();
        
        int getID() {return ID;};
        int getAge() {return age;};
        int getStability() {return stability;};
        int* getSpeed() {return speed;}
                
        void setID (int value);
        void setAge (int value);
        void setStability (int value);
        void setSpeed (int vx, int vy);

        // support function to sort ROIs by ID
        static bool sortByID (const ROI& oROI1, const ROI& oROI2);        
};
}
   
  
#endif
