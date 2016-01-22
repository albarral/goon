#ifndef __GOON_UTILS_RGB_COLOR_H
#define __GOON_UTILS_RGB_COLOR_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 *                                                                         *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

namespace goon
{
class RGBColor
{
private:
    static int same_dist;                      // RGB distance at which two colors are considered the same
    static int similar_dist;                    // RGB distance at which two colors are considered similar
    static int sqr_same_dist;                // same_dist²
    static int sqr_similar_dist;              // similar_dist²
    static const float RED_INTENSITY;
    static const float GREEN_INTENSITY;
    static const float BLUE_INTENSITY;

public:

    // Sets new tolerances to consider same and similar colors
    static void setTolerances (int same_RGB, int similar_RGB);
    
    static int getSameDist () {return same_dist;};
    static int getSimilarDist () {return similar_dist;};
    static int getSqrSameDist () {return sqr_same_dist;};
    static int getSqrSimilarDist () {return sqr_similar_dist;};

    static void mergeValues (cv::Vec3f& color_A, cv::Vec3f& color_B, int q1, int q2);
    // This function merges two RGB colors in the specified quantities. The result is returned as a new color_A.

    // Transform color from RGB to HSV space
    static void toHSV (cv::Vec3f& rgb_color, cv::Vec3f& hsv_color);

    static float getIntensity (float* rgb_color);
    // This function gets the grayscale intensity of a given RGB color.
};
}

#endif
