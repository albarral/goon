#ifndef __GOON_MOTION_MOVE_H
#define __GOON_MOTION_MOVE_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <chrono>

namespace goon 
{
namespace features
{ 
// Base class for measured movements
class Move
{
public:
    // move type
    enum eType
    {
        eTYPE_IMAGE,        // used distances are in the image plane (pixels) 
        eTYPE_WORLD        // used distances are in the real world (centimeters) 
    };
    
 protected:
    int type;
    bool bstarted;        // indicates that movement is being measured (initial point stored)
    std::chrono::steady_clock::time_point t1;   // starting point of the time interval
    int millis;     // measured interval (milliseconds)

 public:
     Move ();
     //~Move();
          
     void setType(int type) {this->type = type;}
     int getType() {return type;}

     std::chrono::steady_clock::time_point getTimeStamp() {return t1;}
     
     // start measuring the movement (stores initial position)
     void init(std::chrono::steady_clock::time_point& t);
     // updates the subject's position and performs the measure. Returns true if measure done ok.
     bool update(std::chrono::steady_clock::time_point& t);     
};

}
}  
#endif
