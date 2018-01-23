/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/cortex/ConfigCortex.h"
		
namespace goon
{
// constructor
ConfigCortex::ConfigCortex()
{
    // binding
    BINDING_OVERLAP_FRACTION = 0.50;
    
    SEGMENTATION_NUM_SAMPLES = 2000;   // 2000 samples per iteration          
    SEGMENTATION_NUMTHREADS = 4;             // 4 threads for segmentation
    // color grid       
    GRID_STEP = 10;        // pixel size of nodes in color grid 
    // floodfill
    FF_ESSENCE_UPDATE_CHANGE_FACTOR = 0.1;      // region's central color will be updated every 10% size increase (initially every 100 pixels)  
    FF_ESSENCE_UPDATE_MIN_CHANGE = 100;
    FF_ESSENCE_HSV_SIMILARITY = 1.0;                      // pixels are accepted in a region if their HSV similarity (vs the region's global essence) is under this value
    // merge
    MERGE_PROXIMITY_GAP = 10;                           // merge regions separated 10 pixels
}


}
