#ifndef __GOON_CORTEX_MODEL_STRUCTURES_H
#define __GOON_CORTEX_MODEL_STRUCTURES_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
	
#include <opencv2/core/core.hpp>
#include "goon/cortex/data/common.h"			
	
namespace goon
{
// data structure to store objects
typedef struct st_object
{
	int ID;
	CvSeq* seq_model_views;
	CvSeq* seq_context;
	int last_date;
	int last_size;
	int last_position[2];
	bool merged;
	int father_id;	
	int num_matches;
}
	st_object;
	
// data structure to store models
typedef struct st_model
{
	int object_ID;
	int view_ID;
	float color[3];
	float scale;
	int num_regions;
	int num_subregions;
	int list_regions[REGIONS_PER_LMK];
}
	st_model;
	
// data structure to store model regions
typedef struct st_model_region
{
	int ID;
	int type;
	CvSeq* seq_subregions;
	float color[3];
	float weight;
	float shape_factor;
	float orientation;
	int num_neighbours;
	st_neighbour neighbours[REGIONS_PER_LMK];
}
	st_model_region;
					  
#endif
}