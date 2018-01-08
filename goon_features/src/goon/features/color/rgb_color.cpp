/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 *                                                                         *
 ***************************************************************************/

#include <cmath>
#include "goon/features/color/rgb_color.h"
		
namespace goon
{
int RGBColor::same_dist = 20;  // RGB color tolerance
int RGBColor::similar_dist = 20; // RGB color tolerance
int RGBColor::sqr_same_dist = RGBColor::same_dist*RGBColor::same_dist;
int RGBColor::sqr_similar_dist = RGBColor::similar_dist*RGBColor::similar_dist;
const float RGBColor::RED_INTENSITY = 0.2989;
const float RGBColor::GREEN_INTENSITY = 0.5870;
const float RGBColor::BLUE_INTENSITY = 0.1140;

// This function sets the RGB perception parameters.
void RGBColor::setTolerances (int same_RGB, int similar_RGB)
{	
    same_dist = same_RGB;
    similar_dist = similar_RGB;
    sqr_same_dist = same_dist*same_dist;
    sqr_similar_dist = similar_dist*similar_dist;
}


// This function merges two RGB colors in the specified quantities. The result is returned as a new color_A.
void RGBColor::mergeValues (cv::Vec3f& color_A, cv::Vec3f& color_B, int q1, int q2)
{
#ifdef DEBUG_MODE
	cout << " init - MergeRGBColors" << endl;
#endif
	float alpha;
						
	if (q1 == 0)
	{
		color_A[0] = color_B[0];
		color_A[1] = color_B[1];
		color_A[2] = color_B[2];
	}
	else
	{
		alpha = (float)q2/(q1+q2);
		
		color_A[0] += alpha * (color_B[0] - color_A[0]);
		color_A[1] += alpha * (color_B[1] - color_A[1]);
		color_A[2] += alpha * (color_B[2] - color_A[2]);
	}
		
#ifdef DEBUG_MODE
	cout << " end  - MergeRGBColors" << endl;
#endif
}


// This function converts a color value from RGB to HSV
cv::Vec3f RGBColor::toHSV (cv::Vec3f& rgbColor)
{
    cv::Vec3f hsvColor;
    float min, max, delta;

    min = fmin( rgbColor[0], rgbColor[1]);
    min = fmin( min, rgbColor[2]);
    max = fmax( rgbColor[0], rgbColor[1]);
    max = fmax( max, rgbColor[2]);

    hsvColor[2] = max;	

    if (max == 0)
    {
            hsvColor[0] = 0;
            hsvColor[1] = 0;
    }
    else
    {
        delta = max - min;
        hsvColor[1] = 255 * delta / max;  

        if (delta == 0)
        {
                hsvColor[0] = 0;
        }
        else
        {
                if( rgbColor[0] == max )
                        hsvColor[0] = 60 * (rgbColor[1] - rgbColor[2]) / delta;	// between yellow & magenta
                else if( rgbColor[1] == max )
                        hsvColor[0] = 60 * (2 + (rgbColor[2] - rgbColor[0]) / delta);	// between cyan & yellow
                else
                        hsvColor[0] = 60 * (4 + (rgbColor[0] - rgbColor[1]) / delta);	// between magenta & cyan

                if( hsvColor[0] < 0 )
                        hsvColor[0] += 360;
        }		
    }		
    return hsvColor;
}


// This function gets the grayscale intensity of a given RGB color.
float RGBColor::getIntensity (float* rgb_color)
{	
	return (RED_INTENSITY * rgb_color[0] + GREEN_INTENSITY * rgb_color[1] + BLUE_INTENSITY * rgb_color[2]);
}

}
