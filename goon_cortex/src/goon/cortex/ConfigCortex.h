#ifndef __GOON_CORTEX_CONFIGCORTEX_H
#define __GOON_CORTEX_CONFIGCORTEX_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace goon
{
class ConfigCortex
{
private:
    // binding
    float BINDING_OVERLAP_FRACTION;      
    
    int SEGMENTATION_NUM_SAMPLES;    // number of seeds used to extract regions
    int SEGMENTATION_NUMTHREADS;         // number of threads used for segmentation
    // color grid 
    int GRID_STEP;        // size of grid nodes (in pixels)
    // floodfill
    float FF_ESSENCE_UPDATE_CHANGE_FACTOR;  // size increase (factor) that triggers a color essence update (in floodfill processes)
    int FF_ESSENCE_UPDATE_MIN_CHANGE;           // minimum size increase (absolute) that triggers a color essence update (in floodfill processes)
    float FF_ESSENCE_HSV_SIMILARITY;                   // HSV distance used for color comparisons between a pixel and the region's color essence.
    // merge
    int MERGE_PROXIMITY_GAP;                 // maximum separation (pixels) between nearby regions to allow them merging


public:
    ConfigCortex();
    //~ConfigCortex();

    // segmentation 
    float getBINDING_OVERLAP_FRACTION() {return BINDING_OVERLAP_FRACTION;}
    
    int getSegmentationNumSamples() {return SEGMENTATION_NUM_SAMPLES;}
    int getSegmentationNumThreads() {return SEGMENTATION_NUMTHREADS;}
    // grids
    int getGridStep() {return GRID_STEP;}
    // floodfiller
    float getColorEssenceUpdateChangeFactor() {return FF_ESSENCE_UPDATE_CHANGE_FACTOR;}
    float getColorEssenceUpdateMinChange() {return FF_ESSENCE_UPDATE_MIN_CHANGE;}    
    float getColorEssenceHSVSimilarity() {return FF_ESSENCE_HSV_SIMILARITY;}
    // merge
    int getMergeProximityGap() {return MERGE_PROXIMITY_GAP;};
    
};
}

#endif
