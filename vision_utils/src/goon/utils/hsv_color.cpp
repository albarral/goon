/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 *                                                                         *
 ***************************************************************************/

#include <cmath>

#include "goon/utils/hsv_color.h"
		
//#define USE_PERCEPTUAL_UNIFORMITY   
//#define KSIN_AMP 0.7            			// amplitude of hue senoidal discriminance
//#define SIGMOID(x) ( 1/(1+exp(-0.2*(x))) )

namespace goon
{
// Constructor
HSVColor::HSVColor()
{	
     SAT_GRAY = 50;
     VAL_DARK = 50;

     SAME_HUE_DIST = 10.0;
     SAME_SATVAL_TOL = 0.25;
     SIMILAR_HUE_DIST = 20.0;
     SIMILAR_SATVAL_TOL = 0.50;
     MIN_SAT_DIST = 25.0;
     MIN_VAL_DIST = 25.0;
     
     initTables ();	
     
     DIST_SAME_COLOR = 1.0;
     
     HUE_STEP = 3;
     SAT_TOL = 0.05;
     VAL_TOL = 0.05;
}


HSVColor::~HSVColor()
{    
}


// This function sets the HSV perception parameters.
void HSVColor::setDistSameColor (float same_HSV)
{
    DIST_SAME_COLOR = same_HSV;
}

	
// This function calculates the Mahalanobis distance between 2 HSV colors. It works with two discriminance levels: SAME_COLOR and SIMILAR_COLOR.
float HSVColor::getDistance (cv::Vec3f& color1, cv::Vec3f& color2, int discriminance_level)
{
    float dif_hue, dif_sat, dif_val, dist_color;
    float Kgray, Kdark;
    float min_sat, min_val, max_sat, max_val;
    float hue_disc, sat_disc, val_disc;

    // get minimum and maximum of sat and val
    if (color1[1] > color2[1])
    {
            max_sat = color1[1];
            min_sat = color2[1];
    }
    else 
    {
            max_sat = color2[1];
            min_sat = color1[1];
    }	
    if (color1[2] > color2[2])
    {
            max_val = color1[2];
            min_val = color2[2];
    }
    else 
    {
            max_val = color2[2];
            min_val = color1[2];
    }

    Kgray = tab_gray_correction [lround(min_sat)];  // reduce H influence if gray region or pixel
    Kdark = tab_dark_correction [lround(min_val)];  // reduce H and S influence if dark region or pixel  

    // obtain discriminance components (relative to maximum values)
    if (discriminance_level == eSAME_COLOR)
    {
            hue_disc = SAME_HUE_DIST;
            sat_disc = max_sat * SAME_SATVAL_TOL;
            val_disc = max_val * SAME_SATVAL_TOL;			
    }
    else
    {
            hue_disc = SIMILAR_HUE_DIST;
            sat_disc = max_sat * SIMILAR_SATVAL_TOL;
            val_disc = max_val * SIMILAR_SATVAL_TOL;			
    }	  	
    sat_disc = fmax(sat_disc, MIN_SAT_DIST);
    val_disc = fmax(val_disc, MIN_VAL_DIST);

    dif_hue = color1[0] - color2[0];
    dif_hue = CYCLIC_HUE_DIF(dif_hue); // cyclic hue correction

    dif_hue = Kgray * Kdark * dif_hue / hue_disc;
    dif_sat = Kdark * (color1[1] - color2[1]) / sat_disc;
    dif_val = (color1[2] - color2[2]) / val_disc;

    // mahalanobis distance (with null cross-covariances)
    dist_color = sqrt( dif_hue*dif_hue + dif_sat*dif_sat + dif_val*dif_val);  

    return (dist_color);
}


	
float HSVColor::getDistance2 (cv::Vec3f& color1, cv::Vec3i& color2)
{
    float dif_hue, color_factor;

    int min_sat = (color1[1] < color2[1] ? color1[1] : color2[1]);
    int min_val = (color1[2] < color2[2] ? color1[2] : color2[2]);			
    // Kgray: reduce H influence if gray regions 
    // Kdark: reduce H and S influence if dark regions		
//    color_factor = tab_gray_correction [min_sat] * tab_dark_correction [min_val];;
    color_factor = tab_gray_correction [min_sat];

    dif_hue = color1[0] - color2[0];
    dif_hue = CYCLIC_HUE_DIF(dif_hue); // cyclic hue correction	
    
    return (color_factor * (std::abs(dif_hue) / SAME_HUE_DIST) + (1.0 - color_factor) * (std::abs(color1[2] - color2[2]) / MIN_VAL_DIST));
}


float HSVColor::getDistance3 (cv::Vec3f& color1, cv::Vec3i& color2)
{
    float dist, dif, disc;
    int mode;

    if (color1[2] < VAL_DARK || color2[2] < VAL_DARK)
        mode = eDARK_ANY;
    else if (color1[1] < SAT_GRAY || color2[1] < SAT_GRAY)
    {
        if (color1[1] < SAT_GRAY && color2[1] < SAT_GRAY)
            mode = eGREY_GREY;
        else
            mode = eCOLOR_GREY;
    }
    else
        mode = eCOLOR_COLOR;
    
    switch (mode)
    {
        case eCOLOR_COLOR:
            dif = color1[0] - color2[0];                
            dif = CYCLIC_HUE_DIF(dif); // cyclic hue correction	
            dist = std::abs(dif) / HUE_STEP;
            break;
            
        case eCOLOR_GREY:
            dif = color1[1] - color2[1];
            disc = color1[1] * SAT_TOL;
            if (disc == 0)
                disc = 5;
            dist = std::abs(dif) / disc;
            break;
            
        case eGREY_GREY:
        case eDARK_ANY:
            dif = color1[2] - color2[2];
            disc = color1[2] * VAL_TOL;
            if (disc == 0)
                disc = 5;
            dist = std::abs(dif) / disc;
            break;
    }
    
    return (dist);
}



// This function merges two HSV colors in the specified quantities. The result is returned as a new color_A.
void HSVColor::mergeValues (float *color_A, float *color_B, int q1, int q2)
{
#ifdef DEBUG_MODE
	cout << " init - MergeHSVColors" << endl;
#endif
	float alpha = (float)q2/(q1+q2);
	float hue_dif;
							
	hue_dif = color_B[0] - color_A[0];
	hue_dif = CYCLIC_HUE_DIF(hue_dif);	
	color_A[0] += alpha * hue_dif;
	color_A[0] = CYCLIC_HUE(color_A[0]);	
	
	color_A[1] += alpha * (color_B[1] - color_A[1]);
	color_A[2] += alpha * (color_B[2] - color_A[2]);

#ifdef DEBUG_MODE
	cout << " end  - MergeHSVColors" << endl;
#endif
}



// This function precalculates the values of the color correction tables
void HSVColor::initTables()
{
    float *ptab;	
    float Kgray, Kdark;

    ptab = tab_gray_correction;				
    for (int x=0; x<SAT_RANGE;  x++)
    {
            if (x < SAT_GRAY) 
                    Kgray = 0.0;
            else
            {
                    Kgray = (x - SAT_GRAY) / 50.0;
                    Kgray = fmin(1.0, Kgray);
            }

            *ptab = Kgray;
            ptab++;
    }

    ptab = tab_dark_correction;				
    for (int x=0; x<VAL_RANGE;  x++)
    {
            if (x < VAL_DARK) 
                    Kdark = 0.0;
            else
            {
                    Kdark = (x - VAL_DARK) / 50.0;
                    Kdark = fmin(1.0, Kdark);
            }

            *ptab = Kdark;
            ptab++;
    }
}



// This function calculates the distance between two hue values considering the varying perceptual discriminance along the hue range.
// The hue perceptual discriminance is minimum around hues R,G,B (atractors) and maximum around hues Yel,Cyan,Mag (discriminators).
// This hue perceptual discriminance is modelled as a senoidal function of the hue value
// The perceptual distance between h1 and h2 is calculated by integrating the perceptual discriminance function between h1 and h2.
// percep_disc(hue) = 1 + 0.7*sin(2PI(hue-30)/120)
// percep_dist(h1,h2) = (h2-h1) - 0.7(120/2PI)[cos(2PI*(h2-30)/120) - cos(2PI*(h1-30)/120)]
// With this senoidal model the minimum perceptual distance between 2 discriminable hues is -> MIN_HUE_DIST = 10
float HSVColor::HuePerceptualDistance (float hue1, float hue2)
{
	float dif_hue, dist_hue;
	float hue_lo, hue_hi;

	dif_hue = fabs(hue2 - hue1);

	if (dif_hue < HUE_RANGE/2)
	{
		hue_hi = fmax(hue1,hue2);
		hue_lo = fmin(hue1,hue2);
	}
  // hue is circular
	else
	{              
		dif_hue = HUE_RANGE - dif_hue;    
		hue_hi = fmin(hue1,hue2) + HUE_RANGE;
		hue_lo = fmax(hue1,hue2);
	}

#ifdef USE_PERCEPTUAL_UNIFORMITY
	dist_hue = dif_hue - KSIN_AMP*K120_2PI*(cos((hue_hi-30)/K120_2PI) -  cos((hue_lo-30)/K120_2PI));
#else
	dist_hue = dif_hue;
#endif

	return (dist_hue);
}




// This function calculates the distance between two sat values considering the varying perceptual discriminance along the sat range.
// The sat perceptual discriminance is minimum near high sats (pure colors) and maximum near low sats (grays).
// This sat perceptual discriminance is modelled as a linear function of the sat value
// The perceptual distance between sat1 and sat2 is calculated by integrating the perceptual discriminance function
// percep_disc(sat) = 2*(1 - sat/256)
// percep_dist(sat1,sat2) = 2|sat2-sat1|*[1 - (sat1+sat2)/(2*256)]
// With this linear model the minimum perceptual distance between 2 discriminable saturations -> MIN_SAT_DIST = 50
float HSVColor::SatPerceptualDistance (float sat1, float sat2)
{
#ifdef USE_PERCEPTUAL_UNIFORMITY
	float dist_sat = 2*fabs(sat2-sat1)*(1 - (sat1+sat2)/(2*SAT_RANGE));
#else
	float dist_sat = fabs(sat2-sat1);
#endif

	return (dist_sat);
}




// This function calculates the distance between two value values considering the varying perceptual discriminance along the value range.
// The int perceptual discriminance is minimum near black levels (int = 0) and maximum near white levels (int = 255).
// This int perceptual discriminance is modelled as a linear function of the int value
// The perceptual distance between val1 and val2 is calculated by integrating the perceptual discriminance function between val1 and val2.
// percep_disc(int) = int*2/256
// percep_dist(val1,val2) = 2|val2-val1|*[(val1+val2)/(2*256)]
// With this linear model the minimum perceptual distance between 2 discriminable intensities is -> MIN_VAL_DIST = 20
float HSVColor::ValPerceptualDistance (float val1, float val2)
{
#ifdef USE_PERCEPTUAL_UNIFORMITY
	float dist_val = fabs(val1-val2)*(val1+val2)/VAL_RANGE;
#else
	float dist_val = fabs(val1-val2);
#endif

	return (dist_val);
}

		

// This function gets the color name from a given hue value.
//int HSVColor::getName (int hue, int sat, int val)
//{
//#ifdef DEBUG_MODE
//	cout << " init - GetColorName" << endl;
//#endif
//
//	int hue_index = (int)floor(hue/10);     // hue sector width = 10
//	
//	char hue_names[36][25] =
//	{"RED+","RED++","ORANGE-","ORANGE","ORANGE+","YELLOW-","YELLOW+","YELLOW_GREEN-","YELLOW_GREEN","YELLOW_GREEN+","GREEN--","GREEN-",
//	"GREEN+","GREEN++","GREEN_CYAN-","GREEN_CYAN","GREEN_CYAN+","CYAN-","CYAN+","CYAN_BLUE-","CYAN_BLUE","CYAN_BLUE+","BLUE--","BLUE-",
//	"BLUE+","BLUE++","VIOLET-","VIOLET","VIOLET+","MAGENTA-","MAGENTA+","MAGENTA_RED-","MAGENTA_RED","MAGENTA_RED+","RED--","RED-"};
//
//	if (val < 2*VAL_DARK)
//		std::cout << "DARK" << std::endl;
//	else
//	{		
//		if (sat < 2*SAT_GRAY)
//		{
//			if (val > VAL_RANGE-VAL_DARK)
//				std::cout << "WHITE"<< std::endl;
//			else
//				std::cout << "GRAY" << std::endl;
//		}
//		else
//		{
//			if (sat < SAT_RANGE/4)
//				std::cout << "poor ";
//			
//			std::cout << hue_names[hue_index] << std::endl;
//		}		
//	}	
//	
//  
//#ifdef DEBUG_MODE
//	cout << " end  - GetColorName" << endl;
//#endif
//
//	return hue_index;
//}



// This function converts a color value from HSV to RGB
void HSVColor::toRGB(cv::Vec3f& hsv_color, cv::Vec3f& rgb_color)
{
    float var_h, var_r, var_g, var_b, var_1, var_2, var_3;
    int var_i;

    float H = hsv_color[0]/HUE_RANGE;
    float S = hsv_color[1]/SAT_RANGE;
    float V = hsv_color[2]/VAL_RANGE;

    if ( S == 0 )                       //HSV values = 0-1
    {
            rgb_color[0] = hsv_color[2];
            rgb_color[1] = hsv_color[2];
            rgb_color[2] = hsv_color[2];
    }
    else
    {
            var_h = H * 6;
            if ( var_h == 6 ) var_h = 0;      //H must be < 1
            var_i = int( var_h );             //Or ... var_i = floor( var_h )
            var_1 = V * ( 1 - S );
            var_2 = V * ( 1 - S * ( var_h - var_i ) );
            var_3 = V * ( 1 - S * ( 1 - ( var_h - var_i ) ) );

            if      ( var_i == 0 ) 
            { var_r = V     ; var_g = var_3 ; var_b = var_1; }
            else if ( var_i == 1 ) 
            { var_r = var_2 ; var_g = V     ; var_b = var_1; }
            else if ( var_i == 2 ) 
            { var_r = var_1 ; var_g = V     ; var_b = var_3; }
            else if ( var_i == 3 ) 
            { var_r = var_1 ; var_g = var_2 ; var_b = V    ; }
            else if ( var_i == 4 ) 
            { var_r = var_3 ; var_g = var_1 ; var_b = V    ; }
            else                   
            { var_r = V     ; var_g = var_1 ; var_b = var_2; }

            rgb_color[0] = var_r * 255;                  //RGB results = 0-255
            rgb_color[1] = var_g * 255;
            rgb_color[2] = var_b * 255;
    }
}



// ****************************************  FUNCTION: IncrementalHueAverage  ****************************************

float HSVColor::incrementalHueAverage (float average, float new_value, float relative_weight)
{
	float dif;
		 
	dif = new_value - average;
	dif = CYCLIC_HUE_DIF (dif); // cyclic hue correction
	
	average += dif * relative_weight;
	average = CYCLIC_HUE(average); // cyclic hue correction

	return (average);
}

}
