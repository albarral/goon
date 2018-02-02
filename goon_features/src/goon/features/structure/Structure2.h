#ifndef __GOON_FEATURES_STRUCTURE2_H
#define __GOON_FEATURES_STRUCTURE2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <string>
#include <vector>
#include "opencv2/core/core.hpp"

#include "goon/features/Blob.h"

 namespace goon
{
// This class represents a 2D structure, a spatial distribution of elements in a 2D body.
// For each element 3 values are stored: polar coordinates & relative scale (all referenced to the body).
// The structure can be computed from different points of the entity. These are called anchors (see eAnchor for valid values).
// Affine invariance is applied to the polar module computation.     
class Structure2
{
public: 
    // matrix depth values
    enum eDepth
    {
        eELEMENT_MODULE,
        eELEMENT_ANGLE,
        eELEMENT_RELATIVE_WEIGHT,
        eELEMENT_DIM
    };
    // anchoring modes
//    enum eAnchor
//    {
//        eANCHOR_CENTER,
//        eANCHOR_NORTH,
//        eANCHOR_EAST,
//        eANCHOR_SOUTH,
//        eANCHOR_WEST,
//        eANCHOR_DIM
//    };
    
 private:
//     int anchor;        // anchor type 
     cv::Mat matStructure;	// matrix representing the body structure (3 depth float matrix)
     Blob oRefBlob;      // reference blob

 public:
     Structure2();
     //~Structure2();
     
    // copy constructor (needed for mat)
    Structure2(const Structure2& oStructure2);  
    // assignment operator (needed for mat)
    Structure2& operator=(const Structure2& oStructure2);
     
    cv::Mat& getMatStructure() {return matStructure;};

    // set reference blob from which the structure will be computed
    void setReferenceBlob(Blob& oBlob);
    // compute the structure of the given elements with respect to the preset reference
    void computeStructure(std::vector<Blob>& listBlobs);
    // clear structure
    void clear();
    
    // return structure description
    std::string toString();

private:    
    // computes the spatial relation of given element with respect to reference
    cv::Vec3f computeSpatialRelation(cv::Point& position, int mass);    
};  
}
  
#endif
