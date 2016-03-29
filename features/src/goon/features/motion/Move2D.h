#ifndef __GOON_MOTION_MOVE2D_H
#define __GOON_MOTION_MOVE2D_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/features/motion/Move.h"

namespace goon 
{
namespace features
{ 
// Class for 2 dimensional movements (translations & size changes)
class Move2D : public Move
{
 private:
     int value[2];      // from value (ie. position)
     int change[2];   // changed quantity (ie. translation)  
     float speed[2];    // units / ms

 public:
     Move2D ();
     //~Move2D();
     
     // start measuring the movement (stores subject position))
     void init(int value[2], std::chrono::steady_clock::time_point& t);
     // updates the subject's position and performs the measure. Returns true if measure done ok.
     bool update(int value[2], std::chrono::steady_clock::time_point& t);
     
     int getValueX() {return value[0];} 
     int getValueY() {return value[1];} 
     int getChangeX() {return change[0];} 
     int getChangeY() {return change[1];} 
     float getSpeedX() {return speed[0];}
     float getSpeedY() {return speed[1];}
     
     std::string toString();
};

}
}  
#endif
