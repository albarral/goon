#ifndef __GOON_RETINAL_CONFIG_H
#define __GOON_RETINAL_CONFIG_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace goon
{
class ConfigRetinal
{
public:    
    static const int BODY_VALUE = 255;
    static const int BORDER_VALUE = 1;
    static const int EXPLORED_VALUE = 255;
private:
    // segmentation 
    float SEGMENTATION_MIN_DETAIL;      // minimum area of details allowed for detection (fraction of image area)
    int SEGMENTATION_NUM_SAMPLES;    // number of seeds used to extract regions
    int SEGMENTATION_NUMTHEADS;         // number of threads used for segmentation
    // color grid 
    int COLORGRID_STEP;        // pixel size of nodes in color grid 
    // floodfill
    float FF_ESSENCE_UPDATE_CHANGE_FACTOR;  // size increase (factor) that triggers a color essence update (in floodfill processes)
    int FF_ESSENCE_UPDATE_MIN_CHANGE;           // minimum size increase (absolute) that triggers a color essence update (in floodfill processes)
    float FF_ESSENCE_HSV_SIMILARITY;                   // HSV distance used for color comparisons between a pixel and the region's color essence.
    // merge
    int MERGE_PROXIMITY_GAP;                 // maximum separation (pixels) between nearby regions to allow them merging


public:
    ConfigRetinal();
    //~ConfigRetinal();

    // segmentation 
    float getSegmentationMinDetail() {return SEGMENTATION_MIN_DETAIL;}
    int getSegmentationNumSamples() {return SEGMENTATION_NUM_SAMPLES;}
    int getSegmentationNumThreads() {return SEGMENTATION_NUMTHEADS;}
    // color grid 
    int getColorGridStep() {return COLORGRID_STEP;}
    // floodfiller
    float getColorEssenceUpdateChangeFactor() {return FF_ESSENCE_UPDATE_CHANGE_FACTOR;}
    float getColorEssenceUpdateMinChange() {return FF_ESSENCE_UPDATE_MIN_CHANGE;}    
    float getColorEssenceHSVSimilarity() {return FF_ESSENCE_HSV_SIMILARITY;}
    // merge
    int getMergeProximityGap() {return MERGE_PROXIMITY_GAP;};
    
};
}

#endif
