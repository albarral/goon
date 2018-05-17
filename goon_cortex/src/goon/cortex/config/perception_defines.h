#ifndef __GOON_CORTEX_PERCEPTION_DEFINES_H
#define __GOON_CORTEX_PERCEPTION_DEFINES_H

/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#define RGB_COLOR_TOLERANCE  20
#define SINGLE_COLOR 	1.0		   	// maximum distance at which 2 HSV colors can be considered a single one

#define SAT_GRAY 50  						// under this saturation all colors are grey
#define VAL_DARK 50  						// under this value all colors are black

#define SAME_HUE_DIST 		10.0 	// maximum hue difference allowed for a SAME color condition
#define SIMILAR_HUE_DIST 	20.0		// maximum hue difference allowed for a SIMILAR color condition
#define SAME_COLOR_TOL 	0.25 	// tolerance allowed in saturation and value components for a SAME color condition
#define SIMILAR_COLOR_TOL 0.50 	// tolerance allowed in saturation and value components for a SIMILAR color condition
#define MIN_SAT_DIST 25.0  			// minimum discriminable sat difference
#define MIN_VAL_DIST  25.0  			// minimum discriminable value difference

#define HUE_RANGE 360
#define SAT_RANGE 256
#define VAL_RANGE 256
#define KSIN_AMP 0.7            			// amplitude of hue senoidal discriminance
#define K120_2PI (120/(2*M_PI))
#define SIGMOID(x) ( 1/(1+exp(-0.2*(x))) )

#define RED_INTENSITY 		0.2989
#define GREEN_INTENSITY 	0.5870
#define BLUE_INTENSITY 		0.1140

// Color labels for different Hue values (in degrees)
#define RED 					0
#define ORANGE 				30
#define YELLOW 				60
#define YELLOW_GREEN 	90
#define GREEN 				120
#define GREEN_CYAN 		150
#define CYAN 					180
#define CYAN_BLUE 			210
#define BLUE 					240
#define BLUE_MAGENTA 	270
#define MAGENTA 			300
#define MAGENTA_RED 	330
#define RED_ROUND 		360
#define COLOR_SECTOR 	10
		
#endif
