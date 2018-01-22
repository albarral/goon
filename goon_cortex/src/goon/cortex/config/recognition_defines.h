#ifndef __GOON_CORTEX_RECOGNITION_DEFINES_H
#define __GOON_CORTEX_RECOGNITION_DEFINES_H

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
	
// MATCHING module	
#define MATCH_QUALITY 50				// quality value required for positive matching (Q10) // (90 for linear quality) // (0.95 for exponential quality)
#define LOCAL_TOLERANCE 0.30		// tolerance value for local structure similarity (applied to position + rotation + scale)
#define SIZE_VARIABILITY 0.30			// variability of a region's size due to occlussion, segmentation or saliency (fraction of region size)
#define SIMILARITY 0.70					// minimum value required for appearance similarity (applied to color + shape) 
#define SIMILARITY_MARGIN 0.10		// safe similarity = minimum value + this margin
#define MAX_SCALE_FACTOR 10  		// maximum scale factor allowed for landmarks comparison
#define MAX_LMK_ROTATION 45  		// maximum rotation allowed for landmarks comparison	

// IDENTIFICATION module
#define GOOD_CONFIDENCE 125		// value required for CONFIDENT recognition 
#define SUPER_CONFIDENCE 200		// value required for SURE recognition 
#define SAFE_CONFIDENCE_RATIO 1.5	// minimum confidence ratio (vs next candidate) required to win a match
#define SAFE_RECOGNITION_WEIGHT 50	// minimum matched weight required for safe recognition (no DB update)	

// SELF + GLOBAL COHERENCE module
#define VISUAL_AREA_NOISE 0.05		// noise area to be discounted from size variation in depth coherence check (% of image area)
#define POSITION_TOLERANCE 		0.10	// maximum position change accepted for context coherence (fraction of previous distance)
#define MIN_POSITION_TOLERANCE 	5	// minimum value for the position tolerance (degrees)
#define SIZE_TOLERANCE 		0.50		// maximum size change accepted for self coherence (fraction of previous size)

#define INVALID -1	


#endif
