/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/motion/TransMotion.h"

namespace goon 
{
// Constructor
TransMotion::TransMotion ()
{
    timeSpan = 1000;    // 1 second
    clear();
}

TransMotion::~TransMotion ()
{
    trajectory.clear();
}

void TransMotion::clear()
{
    trajectory.clear();    
    trackedTime = 0;
    speed[0] = speed[1] = 0.0;
}

void TransMotion::update(int x, int y, int millis)
{
    // add new trajectory point 
    cv::Vec3i newPos(x, y, millis); 
    trajectory.push_back(newPos);
    // removing oldest one if time span exceeded
    trackedTime += millis;
    while (trackedTime > timeSpan)
    {
        trackedTime -= trajectory.front()[2]; 
        trajectory.pop_front();
    }
    
    computeSpeed();
}

// computes motion features (average speed) 
void TransMotion::computeSpeed()
{
    cv::Vec3i firstPos = trajectory.front();
    cv::Vec3i lastPos = trajectory.back();
    
    if (trackedTime > 0)
    {
        float factor = 1.0 / trackedTime;
        speed[0] = (lastPos[0] - firstPos[0]) * factor;
        speed[1] = (lastPos[1] - firstPos[1]) * factor;
    }
}

std::string TransMotion::toString()
{
    std::string desc = "TransMotion: speed=(" + std::to_string(speed[0]) + ", " + std::to_string(speed[1]) + ")\n";            
    for (cv::Vec3i& pos : trajectory)
    {
        desc += "pos = " + std::to_string(pos[0]) + ", " + std::to_string(pos[1]) + ", t = " + std::to_string(pos[2]) + "\n";
    }

    return desc;
}

std::string TransMotion::shortDesc()
{
    std::string desc = "TransMotion: speed=(" + std::to_string(speed[0]) + ", " + std::to_string(speed[1]) + ")";
    return desc;
}

}
							 