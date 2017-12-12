#ifndef __GOON_UTILS_HSV_COLOR_H
#define __GOON_UTILS_HSV_COLOR_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#define HUE_RANGE 360
#define SAT_RANGE 256
#define VAL_RANGE 256

#define CYCLIC_HUE(HUE) ( HUE>360 ?  HUE-360 : ( HUE<0 ? HUE+360 : HUE )  )
#define CYCLIC_HUE_DIF(DIF) ( fabs(DIF)<180 ? DIF : ( DIF>0 ? DIF-360 : DIF+360 ) )				 		 				 		 

namespace goon
{
class HSVColor
{
private:
    enum eCase
    {
        eCOLOR_COLOR,
        eCOLOR_GREY,
        eGREY_GREY,
        eDARK_ANY
    };
    
private:
        int  SAT_GRAY;		// under this saturation all colors are considered grey
        int  VAL_DARK; 		// under this value all colors are considered black
        float  SAME_HUE_DIST;                // maximum hue difference allowed for a SAME color condition
        float  SIMILAR_HUE_DIST;	// maximum hue difference allowed for a SIMILAR color condition
        float  SAME_SATVAL_TOL; 	// tolerance allowed in saturation and value components for a SAME color condition
        float  SIMILAR_SATVAL_TOL;	// tolerance allowed in saturation and value components for a SIMILAR color condition
        float  MIN_SAT_DIST;                  // minimum discriminable sat difference
        float  MIN_VAL_DIST;                  // minimum discriminable value difference
        float tab_gray_correction[SAT_RANGE];
        float tab_dark_correction[VAL_RANGE];	
        float DIST_SAME_COLOR;              // maximum distance at which 2 HSV colors can be considered the same
        
        float HUE_STEP;
        float SAT_TOL;
        float VAL_TOL;

public:

        // discriminance level for color distance measurements
        enum eDiscriminance {
         eSAME_COLOR,
         eSIMILAR_COLOR,
        };

       HSVColor();
        ~HSVColor();

        void setDistSameColor (float same_HSV);
        // This function sets the HSV perception parameters.

        float getDistSameColor () {return (DIST_SAME_COLOR);};
        // This function returns the HSV distance at which two colors are considered the same.

        float getDistance (cv::Vec3f& color1, cv::Vec3f& color2, int discriminance_level);
        // This function calculates the Mahalanobis distance between 2 HSV colors. It works with two discriminance levels: SAME_COLOR and SIMILAR_COLOR.

        // Computes the basic distance between two HSV colors.
        // It only uses a single color component, the one that best captures the essence of the object: hue for saturated objects, and value for unsaturated ones.
        float getDistance2 (cv::Vec3f& color1, cv::Vec3i& color2);

        // Single component (H, S or V) used for distance computation.
        float getDistance3 (cv::Vec3f& color1, cv::Vec3i& color2);

        void mergeValues (float *color_A, float *color_B, int q1, int q2);
        // This function merges two HSV colors in the specified quantities. The result is returned as a new color_A.

        float HuePerceptualDistance (float hue1, float hue2);

        float SatPerceptualDistance (float sat1, float sat2);

        float ValPerceptualDistance (float val1, float val2);

        int getName (int hue, int sat, int val);

        static void toRGB (cv::Vec3f& hsv_color, cv::Vec3f& rgb_color);

        float incrementalHueAverage (float average, float new_value, float relative_weight);

private:
        void initTables();
	// This function precalculates the values of the color correction tables

};
}

#endif
