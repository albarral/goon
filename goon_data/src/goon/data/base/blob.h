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
    cv::Vec2i pos;           // centroid's (x,y) position in the image
    cv::Vec3f covs;             // cx, cy, cxy	
    float shapeFactor;
    int orientation;    
    float scale;
    cv::Vec3f rgb_color;     // color in RGB space
    cv::Vec3f hsv_color;     // color in HSV space

public:
    Blob();
    
    int getMass() {return mass;};
    cv::Vec2i& getPos() {return pos;};
    cv::Vec3f& getCovariances() {return covs;};
    float getShapeFactor() {return shapeFactor;};
    int getOrientation() {return orientation;};
    float getScale() {return scale;};
    cv::Vec3f& getRGB() {return rgb_color;};
    cv::Vec3f& getHSV() {return hsv_color;};
    
    void setMass(int value) {mass = value;};
    void setPos(int x, int y) {pos[0] = x; pos[1] = y;};
    // (xx, yy, xy)
    void setCovariances(float covx, float covy, float covxy) {covs[0] = covx; covs[1] = covy; covs[2] = covxy;};
    void setShapeFactor(float value) {shapeFactor = value;};
    void setOrientation (int value) {orientation = value;};
    void setScale(float value) {scale = value;};
    void setRGB(cv::Vec3f color) {rgb_color = color;};
    void setHSV(cv::Vec3f color) {hsv_color = color;};
   
    virtual void clear();    
    // merges with another blob
    virtual void merge(Blob& oBlob2);
    // computes spatial relation to given blob (affine module, relative angle, relative weight)
    cv::Vec3f computeSpatialRelation2Blob(Blob& oBlob2);
    
    // returns all blob values in string form
    virtual std::string toString();
    virtual std::string shortDesc();    
 }; 
}

#endif
