#ifndef __GOON_PERIPHERAL_UNIT_H
#define __GOON_PERIPHERAL_UNIT_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <chrono>
#include <goon/data/base/blob.h>
#include "goon/features/motion/Move2D.h"

namespace goon
{
// This class represents a Unit
class Unit : public Blob
{
private:
    int ID;
    int age;
    float distance;         // distance to sampled region
    std::vector<int> vec_regions; 
    Blob oTracker;
    Blob preBlob;          // previous blob info
    float growth;               // change of area
    int stability;
    features::Move2D oTransMove;    // translation 2D movement
    static int MAX_STABILITY;
    static float STABLE_SIZE;

public:
        Unit();
        ~Unit();
        
        int getID() {return ID;};
        int getAge() {return age;};
        float getDistance() {return distance;};
        std::vector<int>& getListRegions() {return vec_regions;};
        Blob& getTracker() {return oTracker;};
        float getGrowth() {return growth;};
        int getStability() {return stability;};
        features::Move2D& getTransMove() {return oTransMove;}
        
        static int getMaxStability() {return MAX_STABILITY;};        
        
        
        void setID (int value);
        // clears the unit, making it inactive 
        void clear();
        // prepares an active unit for a new sampling
        void prepare();
        // Initializes the unit with its first region (Blob)
        void initialize (int regionID, Blob& oBlob, std::chrono::steady_clock::time_point& t);
        // adds a new region to the Unit's tracker
        void addRegion (int regionID, Blob& oBlob);
        // absorbs another Unit
        void absorb (Unit& oUnit);
        // updates the Unit with data from its Tracker
        void update(std::chrono::steady_clock::time_point& t);
        
        // computes the distance (Mahalanobis) to the specified (x, y) position
        void computeDistance (int* posxy);

        // computes how the unit has evolved (translation, growth, stability)
        void checkEvolution ();
};
   
}  
#endif
