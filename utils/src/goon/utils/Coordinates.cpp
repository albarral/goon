/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>  
#include "goon/utils/Coordinates.h"  

namespace goon 
{
const float Coordinates::K180_DIV_PI = 57.2958;  // constant 180/PI

void Coordinates::cartesian2polar(float x, float y, float& magnitude, float& angle)
{
        magnitude = sqrt(x*x + y*y);
        angle = atan2 (y, x) * K180_DIV_PI;        
}

}
							 