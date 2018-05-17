#ifndef __GOON_CORTEX_ATTENTION_DEFINES_H
#define __GOON_CORTEX_ATTENTION_DEFINES_H

/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
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

// attention
#define FAST_TARGET_SPEED	10	// angular speed (degrees/s) at which the target's movement is considered fast

// roi search
// #define NEAR_ROIS		200		// distance (in pixels) at which near rois are searched

// inhibition return
#define MAX_INHIBITIONS		10		// maximum number of inhibited areas for focus return

// #define SCAN_DETECTIONS		5	// number of detections used when analysing a landmark
// #define VALID_RECOGNITIONS	3	// number of repeated recognitions required to consider a landmark as valid		
		
#endif
