/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <math.h>

#include "goon/features/structure/Structure2.h"
#include "maty/math/distance.h"

namespace goon
{
// Constructor
Structure2::Structure2 ()
{
}

// copy constructor (needed for mask)    
Structure2::Structure2(const Structure2& oStructure2)
{
    // mat is cloned if not empty
    if (!oStructure2.matStructure.empty())
        matStructure = oStructure2.matStructure.clone(); 
}  

// assignment operator (needed for mask)
Structure2& Structure2::operator=(const Structure2& oStructure2)
{
    // mat is cloned if not empty
    if (!oStructure2.matStructure.empty())
        matStructure = oStructure2.matStructure.clone(); 
    return *this;    
}

void Structure2::setReferenceBlob(Blob& oBlob)
{
    oRefBlob = oBlob;
}
							 

void Structure2::computeStructure(std::vector<Blob>& listBlobs)
{
    // security check
    if (listBlobs.size() == 0)
    {
        clear();
        return; 
    }

    // prepare matrix (single row)
    matStructure = cv::Mat::zeros(1, listBlobs.size(), CV_32FC3);
    
    // for each composing blob compute its structural relation to the reference blob
    int j = 0;
    for (Blob& oBlob : listBlobs)
    {
        matStructure.at<cv::Vec3f>(1, j) = computeSpatialRelation(oBlob.getPos(), oBlob.getMass());
        j++;
    }
}

cv::Vec3f Structure2::computeSpatialRelation(cv::Point& position, int mass)
{
    float relativeWeight; 
    int refArea = oRefBlob.getMass();
    if (refArea > 0)        
        relativeWeight = (float)mass / refArea;
    else
        relativeWeight = 1000.0;
        
    // relative position in polar coordinates
    cv::Point refPos = oRefBlob.getPos();
    int xdif = position.x - refPos.x;
    int ydif = position.y - refPos.y;
    // affine invariant module
    float affineModule = sqrt(maty::Distance::getMahalanobis2s(position, refPos, oRefBlob.getCovariances())); 
    float relativeAngle = atan2(-ydif, xdif)*180/M_PI; // sign of y changed because image Y axis faces down
    
    return cv::Vec3f(affineModule, relativeAngle, relativeWeight);
}

void Structure2::clear()
{
    if (!matStructure.empty())
        matStructure = cv::Scalar(0.0);
}

std::string Structure2::toString()
{
    std::string desc = "Structure2 [reference " + oRefBlob.toString() +
            "\n matrix: \n";
    if (!matStructure.empty())
    {
        // matrix elements
        for (int j=0; j<matStructure.cols; j++)
        {
            cv::Vec3f& structure = matStructure.at<cv::Vec3f>(1, j);
            desc += std::to_string(structure[0]) + "," + std::to_string(structure[1]) + "," + std::to_string(structure[2]) + "\n";
        }
    }    
    return desc;
}
}
