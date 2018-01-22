/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include <math.h>  

#include "goon/features/shape/shape.h"  

namespace goon
{
const float Shape::ORIENTED_SHAPE_FACTOR = 1.1;
const int Shape::UNDEFINED_ORIENTATION = 999;

// Constructor
Shape::Shape ()
{
    centroid[0]=centroid[1]=0;
    covs[0]=covs[1]=covs[2]=0;
    width = height = angle = 0;
    shape_factor = 0;
}


// This function computes a region's shape calculates the centroid and covariances of a region
void Shape::computeShape (cv::Mat& mask, cv::Rect& window)
{
    computeCovariances(mask, window, centroid, covs);

    computeShapeFromCovs(covs);
}
							 

void Shape::computeShapeFromCovs(cv::Vec3f& covs)
{
    computeEllipse(covs[0], covs[1], covs[2], width, height, angle);

    if (height > 0.0)
        shape_factor = width / height;
    else
        shape_factor = 1000;

    // when the shape factor is around 1, orientation is undefined
    if (shape_factor < ORIENTED_SHAPE_FACTOR)
            angle = UNDEFINED_ORIENTATION;    
}

// This function calculates the centroid (x, y) and covariances (cxx, cyy, cxy) of a region
void Shape::computeCovariances (cv::Mat& mask, cv::Rect& window, cv::Vec2i& centroid, cv::Vec3f& covs)
{
    cv::Mat mask_aux;
    st_moments moments;

    // if mask and window have different sizes, get roied mask
    if (window.height != mask.rows || window.width != mask.cols)
        mask_aux = mask(window);
    else 
        mask_aux = mask;
    
    computeMoments (mask_aux, moments);
    
    if (moments.m00 != 0)
    {
        // centroid in the image plane
        centroid[0] = (moments.m10/moments.m00) + window.x;
        centroid[1] = (moments.m01/moments.m00) + window.y;
        covs[0] = moments.mu20/moments.m00;
        covs[1] = moments.mu02/moments.m00;
        covs[2] = moments.mu11/moments.m00;        
    }
}


// This function calculates the principal axes of a main ellipse from its given covariances.
// Resulting angle (in counter clockwise direction) is always inside [-90, 90]
void Shape::computeEllipse (float cxx, float cyy, float cxy, float& width, float& height, float &angle)
{
    float a, b, h, aux;

    a = cxx - cyy;
    b = 2*cxy;
    h = sqrt(a*a + b*b);

    width = sqrt((cxx + cyy + h)/2);
    aux = (cxx + cyy - h);
    if (aux > 0)
        height = sqrt((cxx + cyy - h)/2);
    else
        height = 0.0;
    angle = (atan2(-b, a)/2)*(180/M_PI); // sign of y changed because mask Y axis faces down
}

void Shape::computeMoments (cv::Mat& mask, st_moments& moments)
{
    float xo, yo;
    int x, y;

    // Init values
    moments.m00 = 0;
    moments.m10 = 0;
    moments.m01 = 0;
    moments.m20 = 0;
    moments.m11 = 0;
    moments.m02 = 0;
             
    // walk each row of the mask
    for (y=0; y<mask.rows; y++)
    {
        uchar* Row = mask.ptr(y);
        
        for (x=0; x<mask.cols; x++)
        {
            if (Row[x] != 0)
            {
                moments.m00 ++;
                moments.m10 += x;
                moments.m01 += y;
                moments.m20 += x*x;
                moments.m11 += x*y;
                moments.m02 += y*y;
            }
        }
    }

    // centroid (inside mask window)
    xo = moments.m10/moments.m00;
    yo = moments.m01/moments.m00;
    // central moments
    moments.mu20 = moments.m20 - xo*moments.m10;
    moments.mu02 = moments.m02 - yo*moments.m01;
    moments.mu11 = moments.m11 - xo*moments.m01;
}


// This function merges two ellipses by combining their covariances and centroids.
// The function returns the resulting ellipse in the first position and covariances values.
void Shape::mergeEllipses(cv::Vec2i& pos1, cv::Vec3f& covs1, cv::Vec2i& pos2, cv::Vec3f& covs2, int m1, int m2)
{
    float x1, y1, x2, y2, dx, dy;
    float cx1, cy1, cxy1, cx2, cy2, cxy2;
    float m, w1, w2, w12;

    x1 = pos1[0];
    y1 = pos1[1];
    cx1 = covs1[0];
    cy1 = covs1[1];
    cxy1 = covs1[2];

    x2 = pos2[0];
    y2 = pos2[1];
    cx2 = covs2[0];
    cy2 = covs2[1];
    cxy2 = covs2[2];

    m = m1 + m2;
    if (m!=0)
    {
        w1 = (float)m1 / m;
        w2 = (float)m2 / m;
        w12 = (float)m1*m2 / (m*m);        
    }
    else
        w1 = w2 = w12 = 0.0;
    
    dx = x1 - x2;
    dy = y1 - y2;

    // new covariances
    covs1[0]= w1*cx1 + w2*cx2 + w12*dx*dx;
    covs1[1]= w1*cy1 + w2*cy2 + w12*dy*dy;
    covs1[2]= w1*cxy1 + w2*cxy2 + w12*dx*dy;

    // new position
    pos1[0] = w1*x1 + w2*x2;
    pos1[1] = w1*y1 + w2*y2;
}

}
