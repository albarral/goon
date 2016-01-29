/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/retinal/ConfigRetinal.h"
		
namespace goon
{
// constructor
ConfigRetinal::ConfigRetinal()
{
    // segmentation 
    SEGMENTATION_MIN_DETAIL = 0.001;        // regions accepted from at least 0.1% of image area
    SEGMENTATION_NUM_SAMPLES = 2000;   // 2000 samples per iteration          
    // color grid       
    COLORGRID_STEP = 10;        // pixel size of nodes in color grid 
    // floodfill
    FF_ESSENCE_UPDATE_CHANGE_FACTOR = 0.1;      // region's central color will be updated every 10% size increase (initially every 100 pixels)  
    FF_ESSENCE_UPDATE_MIN_CHANGE = 100;
    FF_ESSENCE_HSV_SIMILARITY = 1.0;                      // pixels are accepted in a region if their HSV similarity (vs the region's global essence) is under this value
}


}
