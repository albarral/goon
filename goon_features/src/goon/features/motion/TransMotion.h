#ifndef __GOON_FEATURES_TRANSMOTION_H
#define __GOON_FEATURES_TRANSMOTION_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <deque>
#include <string>
#include <opencv2/core/core.hpp>

namespace goon 
{
// This class represents a 2D motion (like a translation)
// It contains a body's trajectory for a given time span (parameter) from which a motion can be computed.   
 class TransMotion
{
 private:
    int timeSpan;       // time span for stored trajectory (ms)
    int trackedTime;    // time of stored trajectory (must approach predefined timeSpan)
    std::deque<cv::Vec3i> trajectory;   // stored 2D trajectory (x, y, millis)
    cv::Vec2f speed;    // average speed

 public:
     TransMotion();
     ~TransMotion();
     
     void setTimeSpan(int value) {timeSpan = value;};
     
     // clears the motion
     void clear();
     // adds a new move to the list
     void update(int x, int y, int millis);
       
     // gets the computed average speed (cartesian coordinates)
     cv::Vec2f& getSpeed() {return speed;};
     
     std::string toString(); 
     std::string shortDesc(); 
     
 private: 
    // computes motion features (average speed & acceleration ...) 
     void computeSpeed();
};  

}  
#endif
