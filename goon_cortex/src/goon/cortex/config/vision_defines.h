#ifndef __GOON_CORTEX_VISION_DEFINES_H
#define __GOON_CORTEX_VISION_DEFINES_H

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
				
#define IMAGE_DETAIL 			0.01	// (retinal vision) minimum detail size for image segmentation (fraction of image) 
#define LANDMARK_DETAIL 	0.01 // (visual analysis) minimum detail size for landmark characterization (fraction of landmark)		
#define RECENT_MEMORY		5		// maximum number of recalled recent objects (short term memory)
		
#define CYCLIC_DIF(DIF, CYCLE) ( fabs(DIF)<CYCLE/2 ? DIF : ( DIF>0 ? DIF-CYCLE : DIF+CYCLE ) )
		
#endif
