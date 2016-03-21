#ifndef __GOON_FEATURES_MOTION_H
#define __GOON_FEATURES_MOTION_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <deque>

#include "goon/features/motion/Move2D.h"

namespace goon 
{
namespace features
{     
// This class represents a 2D motion (like a translation)
// It contains a list of consecutive moves (limited to maxMoves) from which a motion can be computed.   
 class Motion
{
 private:
    int maxMoves;
    std::deque<Move2D> listMoves;   // measured moves
    float avgSpeed[2];    // average speed
    float avgAccel[2];      // average acceleration

 public:
     Motion ();
     ~Motion();
     
     // clears the list of moves
     void clear();
     // adds a new move to the list
     void update(features::Move2D& oTransMove);
       
     // gets the computed average speed (cartesian coordinates)
     float* getAverageSpeed() {return avgSpeed;};
     // gets the computed average acceleration (cartesian coordinates)
     float* getAverageAcceleration() {return avgAccel;};
     
 private: 
    // computes motion features (average speed & acceleration ...) 
     void compute();
};  
}
}  
#endif
