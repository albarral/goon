#ifndef __GOON_DATA_RETINA_H
#define __GOON_DATA_RETINA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <mutex>
#include <vector>

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
        std::vector<Region> listRegions;               // list of extracted regions (sorted by ID)         
        std::vector<int> listFinalIDs;                    // list of final region IDs (without the merged ones)

public:
        Retina();
        ~Retina();
                    
        // assignment operator
        Retina& operator= (const Retina& oRetina);

        int getID();
        void setID(int id);
        
        // returns a reference to the list of regions
        std::vector<Region>& getListRegions();
        // adds a new region to the list
        void addRegion (Region& oRegion);

        // returns a reference to the list of final region IDs
        std::vector<int>& getListFinalIDs();
        void setListFinalIDs(std::vector<int>& listFinalIDs);

        // build the list of final valid region IDs (ignoring the merged regions)
        void buildListFinalIDs();        

        // returns the number of extracted regions (in vec_regions)
        int getNumRegions ();
 
        // returns the number of final regions (in vec_final_IDs)
        int getNumFinalIDs ();

        // clears the lists of regions
        void clear();
                
        // returns the region with the specified ID
        Region& getRegion (int ID);         
};

}
#endif
