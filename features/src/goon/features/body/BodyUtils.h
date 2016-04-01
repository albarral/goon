#ifndef __GOON_FEATURES_BODYUTILS_H
#define __GOON_FEATURES_BODYUTILS_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"

#include "goon/features/body/Body.h"

namespace goon 
{
// Utility class for body related computations.
 class BodyUtils
{
 private:
     cv::Mat matOverlaps;     // CV_32FC2 matrix with overlap fractions among bodies (rows: bodies1, columns: bodies2, values: point2f's with (fraction12, fraction21))

 public:
    BodyUtils();
    ~BodyUtils();

    cv::Mat getMatOverlaps() {return matOverlaps;};

    // Computes the overlaps between the two lists of Bodies.
    // It leaves the overlap fraction values in matOverlaps, and indicates the filled positions in listOverlaps
    void computeOverlaps(std::vector<Body> listBodies1, std::vector<Body> listBodies2);     
    
};  

}  
#endif
