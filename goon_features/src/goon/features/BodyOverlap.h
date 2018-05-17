#ifndef __GOON_FEATURES_BODYOVERLAP_H
#define __GOON_FEATURES_BODYOVERLAP_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <vector>
#include "opencv2/core/core.hpp"

#include "goon/features/Body.h"

namespace goon 
{
// Utility class for computing body overlaps (overlapped areas are measured)
 class BodyOverlap
{
 protected:
    cv::Mat matOverlaps;    // matrix of body overlaps 
    std::vector<cv::Vec2i> listCorrespondences;     // list of correspondences
     
 public:
     cv::Mat getMatOverlaps() {return matOverlaps;};
     std::vector<cv::Vec2i>& getCorrespondences() {return listCorrespondences;};
         
    // compute overlaps between two lists of bodies (overlap value is the overlapped area).
    virtual int computeOverlaps(std::list<Body>& listBodies1, std::list<Body>& listBodies2);

 protected:    
    // find correspondences using matOverlaps
    void computeCorrespondences();
};  

}  
#endif
