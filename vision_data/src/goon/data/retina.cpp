/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/retina.h"

namespace goon 
{
Retina::Retina ()
{
    ID = -1;
}

Retina::~Retina()
{
}

int Retina::getNumRegions()  {return vec_regions.size();};

int Retina::getNumFinalRegions()  {return vec_final_IDs.size();};

void Retina::clear()
{
    vec_regions.clear();
    vec_final_IDs.clear();    
    ID = -1;    // first region ID is 0
}

    
void Retina::addRegion(Region& oRegion)
{
    ID++;
    oRegion.setID(ID);
    vec_regions.push_back(oRegion);
}  


void Retina::checkFinalRegions()
{
    std::vector<Region>::iterator it_region = vec_regions.begin();

    // copies all unmerged regions to the final regions list
    while (it_region != vec_regions.end())
    {            
        if (it_region->getType() != Region::eREG_MERGED)
                vec_final_IDs.push_back(it_region->getID());        
     
        it_region++;
    }
}


Region& Retina::getRegion(int ID)
{
    return vec_regions.at(ID);    
}

}
