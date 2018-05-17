#ifndef __GOON_CORTEX_COMMON_H
#define __GOON_CORTEX_COMMON_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#define REGIONS_PER_LMK 	20			// number of regions allowed in each landmark		

/*
// data structure to store appearance info
typedef struct st_appearance
{
    float color[3];             // hsv
    float shape_factor;
    float orientation;
}
st_appearance;
*/
namespace goon
{

// data structure to store coherence info
typedef struct st_neighbour
{
	int ID; 
	float color[3];
	float rel_weight;
	float rel_position[2]; // polar coordinates
	float shape_factor;
	float orientation;
}
	st_neighbour;

// data structure to store the values of an ellipse	
typedef struct st_ellipse
{
	float xo;
	float yo;
	float width;
	float height;
	float angle;
}
  st_ellipse;
	
// data structure to store context info
typedef struct st_context
{
	int object_ID;
	int rel_position[2]; // cartesian coordinates
	float module;
}
	st_context;    
}  
#endif
