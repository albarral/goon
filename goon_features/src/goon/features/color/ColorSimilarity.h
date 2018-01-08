#ifndef __GOON_FEATURES_COLOR_SIMILARITY_H
#define __GOON_FEATURES_COLOR_SIMILARITY_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"
#include "goon/features/color/HSVEssence.h"

// This class performs color similarity computations using local RGB color and global hsv essence.
namespace goon
{
class ColorSimilarity
{
private:
    float SAME_RGB_LOCAL;       // required RGB similarity vs local color
    float SAME_HSV_GLOBAL;     // required HSV similarity vs global color 

public:
    ColorSimilarity();
    ~ColorSimilarity();

    void setRGBSimilarity(float value) {SAME_RGB_LOCAL = value;};
    void setHSVSimilarity(float value) {SAME_HSV_GLOBAL = value;};
    float getRGBSimilarity() {return SAME_RGB_LOCAL;};
    float getHSVSimilarity() {return SAME_HSV_GLOBAL;};

    // computes color similarity between 2 colors
    bool checkSameColor(cv::Vec3f& rgb1, cv::Vec3b& rgb2, HSVEssence& oHSVEssence, cv::Vec3i& hsv2);
    bool checkSameColor(cv::Vec3f& rgb1, cv::Vec3f& rgb2, HSVEssence& oHSVEssence, cv::Vec3f& hsv2);
};
		  	    		  
}  
  
#endif
