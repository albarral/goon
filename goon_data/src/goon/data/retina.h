#ifndef __GOON_DATA_RETINA_H
#define __GOON_DATA_RETINA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <list>
#include <map>
#include <string>

#include "opencv2/core/core.hpp"

#include "goon/data/base/region.h"

namespace goon 
{
// This class represents the visual retina. It holds the list of regions in which the image can be decomposed.
// It's mutex protected to provide thread safety.
class Retina
{
private:
        std::mutex mutex;
        int ID;                                                       // ID of last added region 
        std::list<Region> listRegions;                     // list of extracted regions
        std::map<int, int> mapRegions;                  // map: region.ID - region position in listRegions

public:
        Retina();
        ~Retina();

        // assignment operator (default assignment is implicitly deleted due to mutex copy prohibition)
       Retina& operator= (const Retina& oRetina);
                            
        // returns a reference to the list of regions
        std::list<Region>& getListRegions();
        // returns the number regions 
        int getNumRegions();
         // clears the lists of regions
        void clear();

        // adds a new region to the list (thread safe)
        void addRegion (Region& oRegion);

        // rebuilds mapRegions in coherence with present listRegions
        void updateRegionsMap();
        // returns the Region with the specified ID
        Region* getRegionByID(int ID);
        // returns the Region at the specified position in the list
        Region* getRegionByIndex(int pos);

        // remove the invalid (merged) regions from list
        void removeInvalidRegions();        
        
        // returns description of all retina regions
        std::string toString();    
        // returns short description of all retina regions
        std::string shortDesc();    
        // returns short description of all retina regions with given color range
        std::string showFilterByColor(cv::Vec3b& hsvColor, cv::Vec3b& hsvDeviation);

private:
    // get Region position in list (using the map)
    int getRegionPosition(int regionID);    

};

}
#endif
