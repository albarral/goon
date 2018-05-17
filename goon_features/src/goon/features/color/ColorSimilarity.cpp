/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include "goon/features/color/ColorSimilarity.h"
#include <tron/cv/distance.h>

namespace goon
{
				 				 				 					
// constructor
ColorSimilarity::ColorSimilarity ()
{
    SAME_RGB_LOCAL = 0.0;
    SAME_HSV_GLOBAL = 0.0;
}

// destructor
ColorSimilarity::~ColorSimilarity()
{
}


bool ColorSimilarity::checkSameColor(cv::Vec3f& rgb1, cv::Vec3b& rgb2, HSVEssence& oHSVEssence, cv::Vec3i& hsv2)
{
    return ((tron::Distance::getEuclidean3s(rgb1, rgb2) < SAME_RGB_LOCAL) && oHSVEssence.compare(hsv2) < SAME_HSV_GLOBAL);
}

bool ColorSimilarity::checkSameColor(cv::Vec3f& rgb1, cv::Vec3f& rgb2, HSVEssence& oHSVEssence, cv::Vec3f& hsv2)
{
    return ((tron::Distance::getEuclidean3s(rgb1, rgb2) < SAME_RGB_LOCAL) && oHSVEssence.compare(hsv2) < SAME_HSV_GLOBAL);
}

}
