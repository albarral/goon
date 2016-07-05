#ifndef __GOON_UTILS_AVERAGE_H
#define __GOON_UTILS_AVERAGE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

#include "opencv2/core/core.hpp"

namespace goon
{
class Average
{
public:
    // Updates a 3D average (float) with a new sample (int) causing the given new weight
    static void updateWithSample (cv::Vec3f& average, const cv::Vec3b& new_sample, int new_weight);
    
    // Updates a 3D average (float) with a new sample (float) causing the given new weight
    static void updateWithSample (cv::Vec3f& average, const cv::Vec3f& new_sample, int new_weight);
    
    // Updates an average (float) with a new sample (int) causing the given new weight
    static void updateWithSample (float& average, int new_value, int new_weight);
};
}

#endif
