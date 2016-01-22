/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>  
#include "goon/data/aux/vMotion.h"  

namespace goon 
{
const float vMotion::K180_DIV_PI = 57.2958;  // constant 180/PI

// Constructor
vMotion::vMotion ()
{
    speed_x = speed_y = 0.0;
    angle = speed = 0.0;
}

vMotion::~vMotion ()
{
}

void vMotion::computeSpeeds (int xtrans, int ytrans, float time_millis)
{
    if (time_millis != 0.0)
    {
        speed_x = xtrans / time_millis;
        speed_y = ytrans / time_millis;

        speed = sqrt(speed_x*speed_x + speed_y*speed_y);
        angle = atan2 (ytrans, xtrans) * K180_DIV_PI;        
    }
}
}
							 