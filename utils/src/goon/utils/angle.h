#ifndef __GOON_UTILS_ANGLE_H
#define __GOON_UTILS_ANGLE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *

 ***************************************************************************/

namespace goon
{
// Implements operations on an angle variable (like a color's hue) taking into account its cyclic nature. 
class Angle
{
public:
    // Updates an angle average (float) with a new sample (int) causing the given new weight.
    static void updateAverage (float& average, const int& new_value, int new_weight);
    
    // Updates an angle average (float) with a new sample (float) causing the given new weight.
    static void updateAverage (float& average, const float& new_value, int new_weight);
    
    // Updates an angle average (float) with a new value (float) caused by a set of samples.
    static void updateWeightedAverage (float& average, const float& new_value, int new_samples, int new_weight);
};
}

#endif
