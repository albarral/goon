#ifndef __GOON_CORTEX_RETINAL_DEFINES_H
#define __GOON_CORTEX_RETINAL_DEFINES_H

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


#define RETINAL_SAMPLES 	2000

#define FOVEAL_RADIUS 	5		// radius of the foveal region (in degrees of visual field)
#define SECOND_RADIUS 	10	// radius of the extra foveal region (in degrees of visual field)
#define FIRST_REGION	1		// ID of the first retinal region (0 yields confusion in the retinal regions map)

// SEGMENTATION
#define GRID_STEP 		10	// step (in pixels) used for the local color grid
#define MIN_REGION_SIZE	0.1	// minimum region size for segmentation (in percentage of image area)

#endif
