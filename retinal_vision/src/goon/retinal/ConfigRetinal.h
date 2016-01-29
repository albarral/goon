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
private:
    // segmentation 
    float SEGMENTATION_MIN_DETAIL;      // minimum area of details allowed for detection (fraction of image area)
    int SEGMENTATION_NUM_SAMPLES;    // number of seeds used to extract regions
    // color grid 
    int COLORGRID_STEP;        // pixel size of nodes in color grid 
    // floodfill
    float FF_ESSENCE_UPDATE_CHANGE_FACTOR;  // size increase (factor) that triggers a color essence update (in floodfill processes)
    int FF_ESSENCE_UPDATE_MIN_CHANGE;           // minimum size increase (absolute) that triggers a color essence update (in floodfill processes)
    float FF_ESSENCE_HSV_SIMILARITY;                   // HSV distance used for color comparisons between a pixel and the region's color essence.


public:
    ConfigRetinal();
    //~ConfigRetinal();

    // segmentation 
    float getSegmentationMinDetail() {return SEGMENTATION_MIN_DETAIL;}
    int getSegmentationNumSamples() {return SEGMENTATION_NUM_SAMPLES;}
    // color grid 
    int getColorGridStep() {return COLORGRID_STEP;}
    // floodfiller
    float getColorEssenceUpdateChangeFactor() {return FF_ESSENCE_UPDATE_CHANGE_FACTOR;}
    float getColorEssenceUpdateMinChange() {return FF_ESSENCE_UPDATE_MIN_CHANGE;}    
    float getColorEssenceHSVSimilarity() {return FF_ESSENCE_HSV_SIMILARITY;}
    
};
}

#endif
