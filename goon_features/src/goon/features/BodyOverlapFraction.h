#ifndef __GOON_FEATURES_BODYOVERLAPFRACTION_H
#define __GOON_FEATURES_BODYOVERLAPFRACTION_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>

#include "goon/features/BodyOverlap.h"

namespace goon 
{
// Utility class for computing body overlaps (overlapped fractions are measured)
 class BodyOverlapFraction : public BodyOverlap
{     
 public:
    // compute overlaps between two lists of bodies 
    virtual int computeOverlaps(std::list<Body>& listBodies1, std::list<Body>& listBodies2);
};  

}  
#endif
