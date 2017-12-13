#ifndef __GOON_UTILS_SHAPE_H
#define __GOON_UTILS_SHAPE_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include "opencv2/core/core.hpp"

 namespace goon
{
class Shape
{
 struct st_moments
{
    // spatial moments
    int m00;
    int m10;
    int m01;
    double m20;
    double m11;
    double m02;
    // central moments
    double mu20;
    double mu11;
    double mu02;    
};
     
 public:
     static const float ORIENTED_SHAPE_FACTOR;
     static const int UNDEFINED_ORIENTATION;

 private:
        int centroid[2];		// (x, y)
        cv::Vec3f covs; 		// (cov_xx, cov_yy, cov_xy)
        float width;
        float height;
        float angle;
        float shape_factor;     // is never < 1.0

 public:
     Shape ();
     ~Shape();

    void computeShape(cv::Mat& mask, cv::Rect& window);

    static void computeCovariances(cv::Mat& mask, cv::Rect& window, int* centroid, cv::Vec3f& covs);
    // This function calculates the centroid (x, y) and covariances (cxx, cyy, cxy) of a region

    static void computeEllipse(float cxx, float cyy, float cxy, float& width, float& height, float &angle);
    // This function calculates the principal axes of a main ellipse from its given covariances.
    // Resulting angle (in counter clockwise direction) is always inside [-90, 90]

    static void mergeEllipses(int (&pos1)[2], cv::Vec3f& covs1, int (&pos2)[2], cv::Vec3f& covs2, int m1, int m2);
    // This function merges two ellipses by combining their covariances and centroids.
    // The function returns the resulting ellipse in the first position and covariances values.

    int* getCentroid();
    cv::Vec3f& getCovariances();
    float getWidth();
    float getHeight();
    float getAngle();
    float getShapeFactor();
      
 private:
     // Calculates the spatial and central moments of a mask up to order 2
     static void computeMoments (cv::Mat& mask, st_moments& moments);
};  
}
  
#endif
