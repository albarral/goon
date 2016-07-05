/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/


#include "goon/utils/distance.h"


namespace goon
{
int Distance::getEuclidean2s (cv::Vec2b& vec1, cv::Vec2b& vec2)
{
    int x = vec1[0] - vec2[0];
    int y = vec1[1] - vec2[1];
    
    return (x*x + y*y);
}


int Distance::getEuclidean2s (cv::Vec2i& vec1, cv::Vec2i& vec2)
{
    int x = vec1[0] - vec2[0];
    int y = vec1[1] - vec2[1];
    
    return (x*x + y*y);
}


float Distance::getEuclidean3s(cv::Vec3f& vec1, cv::Vec3f& vec2)
{
    float x = vec1[0] - vec2[0];
    float y = vec1[1] - vec2[1];
    float z = vec1[2] - vec2[2];
    
    return (x*x + y*y + z*z);
}


float Distance::getEuclidean3s(cv::Vec3f& vec1, cv::Vec3b& vec2)
{
    float x = vec1[0] - vec2[0];
    float y = vec1[1] - vec2[1];
    float z = vec1[2] - vec2[2];
    
    return (x*x + y*y + z*z);
}


int Distance::getEuclidean3s(cv::Vec3b& vec1, cv::Vec3b& vec2)
{
    int x = vec1[0] - vec2[0];
    int y = vec1[1] - vec2[1];
    int z = vec1[2] - vec2[2];
    
    return (x*x + y*y + z*z);
}


float Distance::getMahalanobis2s (int* vec1, int* vec2, cv::Vec3f& covs)
{
    int x = vec1[0] - vec2[0]; 
    int y = vec1[1] - vec2[1];
    float cx = covs[0];
    float cy = covs[1];
    float cxy = covs[2];

    return ((x*x*cy+ y*y*cx - 2*x*y*cxy) / (cx*cy - cxy*cxy));
}


float Distance::getMahalanobis3s (cv::Vec3f& vec1, cv::Vec3f& vec2, cv::Vec3f& covs)
{
    float x = vec1[0] - vec2[0];
    float y = vec1[1] - vec2[1];
    float z = vec1[2] - vec2[2];

    return ((x*x/covs[0]) + (y*y/covs[1]) + (z*z/covs[2]));
}


float Distance::getMahalanobis3s (cv::Vec3f& vec1, cv::Vec3b& vec2, cv::Vec3f& covs)
{
    float x = vec1[0] - vec2[0];
    float y = vec1[1] - vec2[1];
    float z = vec1[2] - vec2[2];

    return ((x*x/covs[0]) + (y*y/covs[1]) + (z*z/covs[2]));
}

}
