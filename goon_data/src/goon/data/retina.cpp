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
    listRegions.clear();
}

// assignment operator
Retina& Retina::operator= (const Retina& oRetina)
{
    ID = oRetina.ID;
    listRegions = oRetina.listRegions;
}

std::list<Region>& Retina::getListRegions() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return listRegions;
};

void Retina::addRegion(Region& oRegion)
{
    std::lock_guard<std::mutex> locker(mutex);
    ID++;
    oRegion.setID(ID);
    listRegions.push_back(oRegion);
}  

// remove the invalid (merged) regions from list, reassigning ID's in the new list
void Retina::removeInvalidRegions()
{
    std::lock_guard<std::mutex> locker(mutex);

    ID = 0; // reassign IDs
    std::list<Region>::iterator it_region = listRegions.begin();
    // remove merged regions from list
    while (it_region != listRegions.end())
    {            
        if (it_region->isMerged())
            it_region = listRegions.erase(it_region);
        else 
        {
            it_region->setID(ID++);
            it_region++;
        }
    }
}

int Retina::getNumRegions()  
{
   std::lock_guard<std::mutex> locker(mutex);
   return listRegions.size();
};


void Retina::clear()
{  
    std::lock_guard<std::mutex> locker(mutex);
    listRegions.clear();
    ID = -1;    // first region ID is 0
}
   
Region& Retina::getRegion(int ID)
{
    std::lock_guard<std::mutex> locker(mutex);
    // regions are ordered by ID
    std::list<Region>::iterator it_region = listRegions.begin();
    std::advance(it_region, ID);
    
    return *it_region;
}

std::string Retina::toString()
{
    std::string desc = "Retina:\n";
    std::list<Region>::iterator it_region = listRegions.begin();
    // remove merged regions from list
    while (it_region != listRegions.end())
    {            
        desc += it_region->toString() + "\n";
        it_region++;
    }

    return desc;
}

std::string Retina::shortDesc()
{
    std::string desc = "Retina:\n";
    std::list<Region>::iterator it_region = listRegions.begin();
    // remove merged regions from list
    while (it_region != listRegions.end())
    {            
        desc += it_region->shortDesc() + "\n";
        it_region++;
    }

    return desc;
}
}
