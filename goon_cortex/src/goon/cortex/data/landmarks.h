#ifndef __GOON_CORTEX_LANDMARK_STRUCTURES_H
#define __GOON_CORTEX_LANDMARK_STRUCTURES_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <opencv2/core/core.hpp>
#include "goon/cortex/data/common.h"			
	  	
  
namespace goon
{
// data structure to store landmark regions info
  typedef struct st_lmk_region
{
	int ID;
	int type;
	CvSeq* seq_subregions;
	float weight;
	float color[3];	// hsv
	float shape_factor;
	float orientation;
	int centroid[2];			
	float covs[3]; 	// covariances xx, yy, xy
	int num_neighbours;
	st_neighbour neighbours[REGIONS_PER_LMK];
	int matched;
}
st_lmk_region;
}
#endif
