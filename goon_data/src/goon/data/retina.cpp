/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/retina.h"

namespace goon 
{
Retina::Retina ()
{
    ID = 0;
}

Retina::~Retina()
{
    clear();
}

// assignment operator (necessary due to mutex existence)
Retina& Retina::operator= (const Retina& oRetina)
{
    ID = oRetina.ID;
    listRegions = oRetina.listRegions;
    mapRegions = oRetina.mapRegions;
}

void Retina::clear()
{  
    std::lock_guard<std::mutex> locker(mutex);
    ID = 0;   
    listRegions.clear();
    mapRegions.clear();
}

std::list<Region>& Retina::getListRegions() 
{
    std::lock_guard<std::mutex> locker(mutex);
    return listRegions;
};

void Retina::addRegion(Region& oRegion)
{
    std::lock_guard<std::mutex> locker(mutex);
    oRegion.setID(ID++);
    listRegions.push_back(oRegion);
}  

void Retina::updateRegionsMap()
{
    // clear map
    mapRegions.clear();
    
    // walk list and create associated map
    std::list<Region>::iterator it_Region = listRegions.begin();
    std::list<Region>::iterator it_end = listRegions.end();    
    int pos = 0;
    while (it_Region != it_end)
    {
        mapRegions.emplace(it_Region->getID(), pos);        
        it_Region++;
        pos++;
    }    
}

Region* Retina::getRegionByID(int ID)
{
    // first we get the mapped position
    int pos = getRegionPosition(ID);
    // then we access the Region
    return getRegionByIndex(pos);
}

Region* Retina::getRegionByIndex(int pos)
{
    // if position exists, return Region pointer
    if (pos >= 0 && pos < listRegions.size())
    {
        std::list<Region>::iterator it_Region = listRegions.begin();
        std::advance(it_Region, pos);
        return &(*it_Region);    
    }
    // otherwise, return 0
    else
        return 0;
}

// remove the invalid (merged) regions from list, reassigning ID's in the new list
void Retina::removeInvalidRegions()
{
    std::lock_guard<std::mutex> locker(mutex);

    std::list<Region>::iterator it_region = listRegions.begin();
    // remove merged regions from list
    while (it_region != listRegions.end())
    {            
        if (it_region->isMerged())
            it_region = listRegions.erase(it_region);
        else 
            it_region++;
    }
}

int Retina::getNumRegions()  
{
   std::lock_guard<std::mutex> locker(mutex);
   return listRegions.size();
}

int Retina::getRegionPosition(int regionID)
{
    try
    {
        // get mapped position of given Region
        return mapRegions.at(regionID);
    }    
    catch (const std::out_of_range& oor) 
    {
        // not found
        return -1;
    }
}

std::string Retina::toString()
{
    std::string desc = "Retina:\n";
    std::list<Region>::iterator it_region = listRegions.begin();
    // walk all regions from list
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
    // walk all regions from list
    while (it_region != listRegions.end())
    {            
        desc += it_region->shortDesc() + "\n";
        it_region++;
    }

    return desc;
}

std::string Retina::showFilterByColor(cv::Vec3b& hsvColor, cv::Vec3b& hsvDeviation)
{
    std::string desc = "Retina (filtered color):\n";
    
    cv::Vec3b hsvColor1 = hsvColor - hsvDeviation;
    cv::Vec3b hsvColor2 = hsvColor + hsvDeviation;
            
    std::list<Region>::iterator it_region = listRegions.begin();
    // walk all regions from list
    while (it_region != listRegions.end())
    {
        cv::Vec3f& regionColor = it_region->getHSV();
        // check if region color is in given range
        if ((regionColor[0] > hsvColor1[0] && regionColor[0] < hsvColor2[0]) && 
                (regionColor[1] > hsvColor1[1] && regionColor[1] < hsvColor2[1]) &&
                (regionColor[2] > hsvColor1[2] && regionColor[2] < hsvColor2[2]))
            desc += it_region->shortDesc() + "\n";
        
        it_region++;
    }

    return desc;
}
}
