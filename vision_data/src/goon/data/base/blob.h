#ifndef __GOON_DATA_BLOB_H
#define __GOON_DATA_BLOB_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

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
    cv::Vec3f  rgb_color;     // color in RGB space
    cv::Vec3f  hsv_color;     // color in HSV space
    cv::Rect window;

public:
    Blob();
    
    int getMass() {return mass;};
    int* getPos() {return pos;};
    cv::Vec3f& getCovariances() {return covs;};
    cv::Vec3f& getRGB() {return rgb_color;};
    cv::Vec3f& getHSV() {return hsv_color;};
    cv::Rect& getWindow() {return window;};
    
    void setMass (int value) {mass = value;};
    void setPos (int x, int y) {pos[0] = x; pos[1] = y;};
    // (xx, yy, xy)
    void setCovariances (float covx, float covy, float covxy);
    void setRGB (cv::Vec3f& color) {rgb_color = color;};
    void setHSV (cv::Vec3f& color) {hsv_color = color;};
    void setWindow (cv::Rect& rwindow) {window = rwindow;};
   	        
    // merges another blob with this one
    void merge (Blob& oBlob2);
    // updates all blob values with those of another blob
    void updateBlob(Blob& oBlob2);
 }; 
}

#endif
