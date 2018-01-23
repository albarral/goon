#ifndef __GOON_MAIN_BODYUTILS_H
#define __GOON_MAIN_BODYUTILS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "goon/data/base/Body.h"

namespace goon 
{
struct st_bodyOverlap
{
    int body2;            // body 
    float overlap1;     // overlapped fraction of 1st body 
    float overlap2;     // overlapped fraction of 2nd body 
};

// Utility class for body related computations.
 class BodyUtils
{
 public:
    // Computes the overlap between a given body and a list of bodies.
    // The list of positive overlaps is returned.
    static std::vector<st_bodyOverlap> computeOverlaps(Body oBody, std::vector<Body> listBodies);

    // Gets the best overlap between a given body and a list of bodies.
    static st_bodyOverlap getBestOverlap(Body oBody, std::vector<Body> listBodies);    
};  

}  
#endif
