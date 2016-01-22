/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/utils/average.h"

namespace goon
{
// Updates an average color with a new color sample (int)
void Average::updateWithSample (cv::Vec3f& average, const cv::Vec3b& new_sample, int new_weight)
{
    float alpha = 1.0 / new_weight;        
    for (int i=0; i<3; i++)
        average[i] += alpha * (new_sample[i] - average[i]);
}

// Updates an average color with a new color sample (float)
void Average::updateWithSample (cv::Vec3f& average, const cv::Vec3f& new_sample, int new_weight)
{
    float alpha = 1.0 / new_weight;        
    for (int i=0; i<3; i++)
        average[i] += alpha * (new_sample[i] - average[i]);
}

void Average::updateWithSample(float& average, int new_value, int new_weight)
{
    float alpha = 1.0 / new_weight;        

    average += alpha * (new_value - average);    
}

}
