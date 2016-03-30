#ifndef __GOON_FEATURES_BODYUTILS_H
#define __GOON_FEATURES_BODYUTILS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <utility>
#include <vector>
#include "opencv2/core/core.hpp"

#include "goon/features/body/Body.h"

namespace goon 
{
namespace features
{     
// Utility class for body related computations.
 class BodyUtils
{
 private:
     cv::Mat matOverlaps;               // matrix where the overlap fractions are stored (num bodies 1 x num bodies 2))
     std::vector<std::pair<int,int>> listOverlaps;  // list indicating the matrix nodes with have positive values

 public:
    BodyUtils();
    ~BodyUtils();

    cv::Mat getMatOverlaps() {return matOverlaps;};
    std::vector<std::pair<int,int>>& getListOverlaps() {return listOverlaps;};

    // Computes the overlaps between the two lists of Bodies.
    // It leaves the overlap fraction values in matOverlaps, and indicates the filled positions in listOverlaps
    void computeOverlaps(std::vector<Body> listBodies1, std::vector<Body> listBodies2);     
    
};  

}
}  
#endif
