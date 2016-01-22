#ifndef __GOON_RETINAL_MERGE_H
#define __GOON_RETINAL_MERGE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <set>
#include <opencv2/core/core.hpp>
#include <log4cxx/logger.h>

#include <goon/data/retina.h>

namespace goon
{
class Merge
{
private:
        static log4cxx::LoggerPtr logger;
        int GAP;                // maximum separation (pixels) between regions to allow them merging
        cv::Mat mat_proximity;
        std::set<int> set_regions;   // set of regions to form a collection (automatically avoids duplications)

public:
    Merge ();
    ~Merge ();

    // change of parameters
    void setSizes (int img_w, int img_h);
    void setGap(int value) {GAP = value;};
    
    int doMerge (Retina& oRetina);
    // This function merges all adjacent regions with similar color.

private:

    // Checks if there are nearby regions with similar color that can be merged.
    void checkProximityMerge(Retina& oRetina);

    // Checks whether two region grids overlap or not.
    bool checkGridsOverlap(cv::Mat& mat_grid1, cv::Mat& mat_grid2);

    // This function merges similar nearby regions into new regions.
    // Merged regions become subregions and new regions are collections.
    int mergeRegions(Retina& oRetina);
    
    // Creates a collection by merging a set of regions into the specified base region.
    void createCollection (Region& oBaseRegion, Retina& oRetina);
        
    // (Recurrent function) Iteratively builds the list of regions that are to be merged with the specified one.
    void checkRegions2Merge (int regionID);
};
  		  	     
}  
		  
#endif
