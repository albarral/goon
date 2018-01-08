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
#include "goon/retinal/Grid.h"
#include "goon/data/base/ColorBody.h"
#include "goon/features/color/ColorSimilarity.h"

namespace goon
{
class Merge
{
private:
        static log4cxx::LoggerPtr logger;
        int proximityGAP;                // maximum separation (pixels) between regions to allow them merging
        cv::Mat mat_proximity;       // matrix used to associate regions to be merged   
        std::set<int> setCollectionRegions;   // set of regions to form a collection (automatically avoids duplications)
        Grid oGrid;                      // class for handling body grids
        ColorSimilarity oColorSimilarity;

public:
    Merge();
    ~Merge();

    void init(int img_w, int img_h);

    // change of parameters
    void setGap(int value);
    
    int doMerge(Retina& oRetina);
    // This function merges all adjacent regions with similar color.

private:

    // Checks if there are nearby regions with similar color that can be merged.
    void checkProximityMerge(Retina& oRetina);

    // checks whether two color bodies are mergeable
    bool checkMergeableBodies(ColorBody& oBody1, ColorBody& oBody2, cv::Rect& window);
    
    // This function merges similar nearby regions into new regions.
    // Merged regions become subregions and new regions are collections.
    int mergeRegions(Retina& oRetina);
    
    // Creates a collection by merging a set of regions into the specified base region.
    void createCollection2(Region& oBaseRegion, Retina& oRetina);
        
    // (Recurrent function) Iteratively builds the list of regions that are to be merged with the specified one.
    void checkRegions2Merge(int regionID);
};
  		  	     
}  
		  
#endif
