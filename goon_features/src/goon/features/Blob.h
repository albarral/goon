#ifndef __GOON_FEATURES_BLOB_H
#define __GOON_FEATURES_BLOB_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/core/core.hpp>

namespace goon 
{
// This class represents a blob, the basic visual entity in the goon vision system.
// A blob has a characteristic shape (covariances), mass and position.
class Blob
{
protected:
    int mass;                  // area in pixels
    cv::Point pos;           // centroid's (x,y) position in the image
    cv::Vec3f covs;             // cx, cy, cxy	
    float shapeFactor;
    int orientation;    

public:
    Blob();
    
    int getMass() {return mass;};
    cv::Point& getPos() {return pos;};
    cv::Vec3f& getCovariances() {return covs;};
    float getShapeFactor() {return shapeFactor;};
    int getOrientation() {return orientation;};
    
    void setMass(int value) {mass = value;};
    void setPos(int x, int y) {pos.x = x; pos.y = y;};
    // (xx, yy, xy)
    void setCovariances(float covx, float covy, float covxy) {covs[0] = covx; covs[1] = covy; covs[2] = covxy;};
    void setShapeFactor(float value) {shapeFactor = value;};
    void setOrientation (int value) {orientation = value;};
   
    virtual void clear();    
    // merges with another blob
    virtual void merge(Blob& oBlob2);
    
    // returns all blob values in string form
    virtual std::string toString();
    virtual std::string shortDesc();    
 }; 
}

#endif
