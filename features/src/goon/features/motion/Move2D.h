#ifndef __GOON_MOTION_MOVE2D_H
#define __GOON_MOTION_MOVE2D_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/motion/Move.h"

namespace goon 
{
namespace features
{ 
// Class for 2 dimensional movements (translations & size changes)
class Move2D : public Move
{
 private:
     int value[2];  // previous position
     int change[2];
     float speed[2];

 public:
     Move2D ();
     //~Move2D();
     
     // start measuring the movement (stores subject position))
     void start(int value[2], std::chrono::steady_clock::time_point& t);
     // updates the subject's position and performs the measure. Returns true if measure done ok.
     bool update(int value[2], std::chrono::steady_clock::time_point& t);
     
     int getXChange() {return change[0];} 
     int getYChange() {return change[1];} 
     float getXSpeed() {return speed[0];}
     float getYSpeed() {return speed[1];}
};

}
}  
#endif
