#ifndef __GOON_DATA_RETINA_H
#define __GOON_DATA_RETINA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "goon/data/base/region.h"

namespace goon 
{
class Retina
{
private:
        int ID;                                                       // ID of last added region (equal to region's index in the list)
        std::vector<Region> vec_regions;               // list of extracted regions (sorted by ID)         
        std::vector<int> vec_final_IDs;                    // list of final region IDs (without the merged ones)

public:
        Retina();
        ~Retina();

        // returns a reference to the list of regions
        std::vector<Region>& getListRegions() {return vec_regions;};

        // returns a reference to the list of final regions
        std::vector<int>& getFinalRegions() {return vec_final_IDs;};

        // returns the number of extracted regions (in vec_regions)
        int getNumRegions ();
 
        // returns the number of final regions (in vec_final_IDs)
        int getNumFinalRegions ();

        // clears the lists of regions
        void clear();

        // adds a new region to the list
        void addRegion (Region& oRegion);

        // Builds the list of final valid region IDs (ignoring merged regions)
        void checkFinalRegions();        
                
        // returns the region with the specified ID
        Region& getRegion (int ID);                               
};

}
#endif
