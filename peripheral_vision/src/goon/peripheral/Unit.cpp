/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/peripheral/Unit.h"
#include "goon/utils/distance.h"

namespace goon
{
int Unit::MAX_STABILITY = 5;
float Unit::STABLE_SIZE = 0.70;	// a unit is considered stable if its size similarity is kept above this value 

Unit::Unit ()
{
    ID = -1;
    age = 0;
    stability = 0;
}

Unit:: ~Unit ()
{
}

void Unit::setID(int value) {ID = value;}

void Unit::clear()
{
    setMass(0);
    vec_regions.clear();
}

void Unit::prepare()
{
    oTracker.setMass(0);
    vec_regions.clear();
    // store present blob data
    preBlob = *this;
}

// Initializes the unit with its first region (Blob)
void Unit::initialize (int regionID, Blob& oBlob, std::chrono::steady_clock::time_point& t)
{    
    updateBlob(oBlob);        
    
    oTracker = oBlob;
    vec_regions.push_back(regionID);  
    
    age = 0;
    growth = 0;
    stability = 0; 
    oTransMove.init(oBlob.getPos(), t);    
}


// adds a new region (Blob) to the Unit's tracker
void Unit::addRegion (int regionID, Blob& oBlob)
{    
    // if first region, init tracker with the region's values
    if (vec_regions.empty()) 
        oTracker = oBlob;
    // otherwise, merge the region into the tracker
    else
        oTracker.merge(oBlob);

    vec_regions.push_back(regionID);
}


// absorbs another Unit (blob, tracker and regions)
void Unit::absorb (Unit& oUnit)
{
    merge(oUnit);
    
    oTracker.merge(oUnit.getTracker());

    // transfer regions from absorbed unit
    vec_regions.insert(vec_regions.end(), oUnit.getListRegions().begin(), oUnit.getListRegions().end());            	      
}


// updates the Unit with data from its Tracker and recomputes some features (stability, translation)
void Unit::update (std::chrono::steady_clock::time_point& t)
{    
    if (oTracker.getMass() > 0)
    {
        // control age's limit
        if (age < 10000)
            age++;
        
        updateBlob(oTracker);
        
        // update movement info
        oTransMove.update(pos, t);
        
        // check how the unit has evolved (not for new units)
        checkEvolution();
    }
    else
        clear();
}


void Unit::computeDistance(int* posxy) 
{
    distance = Distance::getMahalanobis2s (posxy, pos, covs);
}


// computes how the unit has evolved (translation, growth, stability)
void Unit::checkEvolution ()
{
    float size_sim;	

    // ignore new units
    if (age <= 1)
        return;

    growth = (float)mass / preBlob.getMass();

    if (growth > 1.0)
            size_sim = sqrt(1.0/growth);
    else
            size_sim = sqrt(growth);		 

    if (size_sim > STABLE_SIZE)
    {
        if (stability < MAX_STABILITY)
                stability++;
    }
    else            
        stability = 0;				
}

}
