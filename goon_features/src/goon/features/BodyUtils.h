#ifndef __GOON_MAIN_BODYUTILS_H
#define __GOON_MAIN_BODYUTILS_H

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
// Utility class for body related computations.
 class BodyUtils
{
 private:
    cv::Mat matOverlaps;    // matrix of body overlaps (mat<int> overlap areas) 
    std::vector<cv::Vec2i> listCorrespondences;     // list of correspondences
     
 public:
     cv::Mat getMatOverlaps() {return matOverlaps;};
     std::vector<cv::Vec2i>& getCorrespondences() {return listCorrespondences;}
         
    // compute overlaps between two lists of bodies.
    int computeBodiesOverlaps(std::list<Body> listBodies1, std::list<Body> listBodies2);
    
    // find correspondences between both lists of bodies based in their overlap
    int findBodyCorrespondences();

    // computes the overlapped fractions between a body and a list of bodies
    static std::vector<cv::Vec2f> computeBodyOverlappedFractions(Body oBody, std::vector<Body> listBodies);    
};  

}  
#endif
