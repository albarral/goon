#ifndef __GOON_CORTEX_REGIONS_H
#define __GOON_CORTEX_REGIONS_H

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
		
  namespace goon
{
// Region types
	enum{
 eREG_SIMPLE, 
 eREG_MERGED, 
 eREG_COLLECTION, 
	};	
	
// data structure to store detected regions during segmentation and merge
 typedef struct st_region
{	  
	int ID;
	int type;
	float color[3];		// hsv color
	float rgb_color[3];	// rgb color
	float color_dev;		// average rgb color deviation
	int pixels;
	IplImage* mask;
	CvRect window;
	int centroid[2];
	float covs[3]; 		// (cov_xx, cov_yy, cov_xy)
	int seed[2];	// temp
	int merge_regions;
	CvSeq* seq_subregions;
	CvMat* mat_grid;
}
  st_region;
		     

}
#endif
