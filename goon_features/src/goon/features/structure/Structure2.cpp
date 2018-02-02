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
    point.x = point.y = 0.0;
    covs[0] = covs[1] = covs[2] = 0.0;
    area = 0;
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

void Structure2::setReference(cv::Point& refPoint, cv::Vec3f& refCovs, int refArea)
{
    point = refPoint;
    covs = refCovs;
    area = refArea;    
}
							 

void Structure2::computeStructure(std::vector<cv::Vec3i>& listElements)
{
    // security check
    if (listElements.size() == 0)
    {
        clear();
        return; 
    }

    // prepare matrix (single row)
    matStructure = cv::Mat::zeros(1, listElements.size(), CV_32FC3);
    
    // for each element compute its structural relation to the reference
    int j = 0;
    for (cv::Vec3i& element : listElements)
    {
        cv::Point pos(element[0], element[1]);
        matStructure.at<cv::Vec3f>(1, j) = computeSpatialRelation(pos, element[2]);
        j++;
    }
}

cv::Vec3f Structure2::computeSpatialRelation(cv::Point& position, int mass)
{
    float relativeWeight; 
    if (area > 0)        
        relativeWeight = (float)mass / area;
    else
        relativeWeight = 1000.0;
        
    // relative position in polar coordinates
    int xdif = position.x - point.x;
    int ydif = position.y - point.y;
    // affine invariant module
    float affineModule = sqrt(maty::Distance::getMahalanobis2s(position, point, covs)); 
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
    std::string desc = "Structure2 [reference (" + std::to_string(point.x) + ", " + std::to_string(point.y) + ")" +
            ", area = " + std::to_string(area) + 
            ", covs = (" + std::to_string(covs[0]) + "," + std::to_string(covs[1]) + "," + std::to_string(covs[2]) + ")" +
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
