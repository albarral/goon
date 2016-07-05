/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "goon/utils/angle.h"

namespace goon
{
// Updates an average color with a new color sample (int)
void Angle::updateAverage(float& average, const int& new_value, int new_weight)
{
    float alpha = 1.0 / new_weight;            
    float dif = new_value - average;
    
    // always keep differences below 180 degrees (cyclic behaviour)
    if (std::abs(dif) > 180)
    {
        dif += (dif > 0 ? -360 : 360); 
    }        
    
    average += alpha * dif;
    
    // leave average between 0 and 359.
    if (average < 0)
        average += 360;
    else if (average >= 360)
        average -= 360;
}


// Updates an average color with a new color sample (float)
void Angle::updateAverage(float& average, const float& new_value, int new_weight)
{
    float alpha = 1.0 / new_weight;            
    float dif = new_value - average;
    
    // always keep differences below 180 degrees (cyclic behaviour)
    if (std::abs(dif) > 180)
    {
        dif += (dif > 0 ? -360 : 360); 
    }        
    
    average += alpha * dif;
    
    // leave average between 0 and 359.
    if (average < 0)
        average += 360;
    else if (average >= 360)
        average -= 360;
}


void Angle::updateWeightedAverage(float& average, const float& new_value, int new_samples, int new_weight)
{
    float alpha = new_samples/new_weight;    
    float dif = new_value - average;
    
    // always keep differences below 180 degrees (cyclic behaviour)
    if (std::abs(dif) > 180)
    {
        dif += (dif > 0 ? -360 : 360); 
    }        
    
    average += alpha * dif;
    
    // leave average between 0 and 359.
    if (average < 0)
        average += 360;
    else if (average >= 360)
        average -= 360;    
}

}
