#ifndef __GOON_DATA_BLOB_H
#define __GOON_DATA_BLOB_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>

namespace goon 
{
// This class represents a blob, the basic visual entity in the goon vision system.
// A blob has a characteristic color, shape (covariances) and position.
class Blob
{
protected:
    int mass;                  // area in pixels
    int pos[2];                 // centroid's (x,y) position in the image
    cv::Vec3f covs;             // cx, cy, cxy	
    cv::Vec3f rgb_color;     // color in RGB space
    cv::Vec3f hsv_color;     // color in HSV space

public:
    Blob();
    
    int getMass() {return mass;};
    int* getPos() {return pos;};
    cv::Vec3f& getCovariances() {return covs;};
    cv::Vec3f& getRGB() {return rgb_color;};
    cv::Vec3f& getHSV() {return hsv_color;};
    
    void setMass(int value) {mass = value;};
    void setPos(int x, int y) {pos[0] = x; pos[1] = y;};
    // (xx, yy, xy)
    void setCovariances(float covx, float covy, float covxy) {covs[0] = covx; covs[1] = covy; covs[2] = covxy;};
    void setRGB(cv::Vec3f color) {rgb_color = color;};
    void setHSV(cv::Vec3f color) {hsv_color = color;};
   	        
    // merges with another blob
    virtual void merge(Blob& oBlob2);

    // returns all blob values in string form
    virtual std::string toString();
    virtual std::string shortDesc();    
 }; 
}

#endif
