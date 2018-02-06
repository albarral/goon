#ifndef __GOON_CORTEX_MATCHES_H
#define __GOON_CORTEX_MATCHES_H

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

	
namespace goon
{
// data structure to store matching info
typedef struct st_match
{
    int matched_object;
//    int matched_view;
    float quality;
    float self_evidence;
    float context_evidence;
    float confidence;
    float lmk_matched_weight;
    float mod_matched_weight;
    float lowest_similarity;
}
st_match;	

// data structure to store anchor matching info
typedef struct st_anchor_match
{
	float rotation;
	float color_similarity;
	float shape_similarity;
}
st_anchor_match;
}
#endif	
