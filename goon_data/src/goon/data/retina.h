#ifndef __GOON_DATA_RETINA_H
#define __GOON_DATA_RETINA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <list>
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
        int ID;                                                       // ID of last added region (equal to region's index in the list)
        std::list<Region> listRegions;                     // list of extracted regions (sorted by ID)         

public:
        Retina();
        ~Retina();
                    
        // assignment operator
        Retina& operator= (const Retina& oRetina);
        
        // returns a reference to the list of regions
        std::list<Region>& getListRegions();
        // adds a new region to the list (thread safe)
        void addRegion (Region& oRegion);

        // remove the invalid (merged) regions from list, reassigning ID's in the new list
        void removeInvalidRegions();        

        // returns the number of extracted regions (in vec_regions)
        int getNumRegions();
 
        // clears the lists of regions
        void clear();
                
        // returns the region with the specified ID
        Region& getRegion (int ID);         
        
        // returns description of all retina regions
        std::string toString();    
        // returns short description of all retina regions
        std::string shortDesc();    
        // returns short description of all retina regions with given color range
        std::string showFilterByColor(cv::Vec3b& hsvColor, cv::Vec3b& hsvDeviation);

};

}
#endif
