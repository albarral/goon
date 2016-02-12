/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/base/blob.h"
#include "goon/utils/rgb_color.h"
#include "goon/utils/shape.h"
	
namespace goon 
{
// constructor
Blob::Blob ()
{
    mass = 0;
    pos[0] = pos[1] = 0;
    covs[0] = covs[1] = covs[2] = 0.0;
    window = cv::Rect (0,0,0,0);
}

// copy constructor (needed for vectors)
Blob::Blob(const Blob& oBlob)    
{
    mass = oBlob.mass;
    pos[0] = oBlob.pos[0];
    pos[1] = oBlob.pos[1];    
    covs = oBlob.covs;
    rgb_color = oBlob.rgb_color;
    hsv_color = oBlob.hsv_color;        	
    window = oBlob.window;
}

// assignment operator
Blob& Blob::operator=(const Blob& oBlob)
{
    mass = oBlob.mass;
    pos[0] = oBlob.pos[0];
    pos[1] = oBlob.pos[1];    
    covs = oBlob.covs;
    rgb_color = oBlob.rgb_color;
    hsv_color = oBlob.hsv_color;        	
    window = oBlob.window;
    return *this;
}

void Blob::setMass (int value) {mass = value;}

void Blob::setPos (int x, int y) {pos[0] = x; pos[1] = y;}    

void Blob::setCovariances (float covx, float covy, float covxy) {covs[0] = covx; covs[1] = covy; covs[2] = covxy;}


void Blob::setRGB (cv::Vec3f& color) 
{
    for (int i=0; i<3; i++)
        rgb_color[i] = color[i];
}


void Blob::setHSV (cv::Vec3f& color) 
{
    for (int i=0; i<3; i++)
        hsv_color[i] = color[i];
}


void Blob::setWindow(cv::Rect& rwindow) {window = rwindow;}


void Blob::merge(Blob& oBlob2)
{
    Shape::mergeEllipses (pos, covs, oBlob2.pos, oBlob2.covs, mass, oBlob2.mass);
    
    RGBColor::mergeValues(rgb_color, oBlob2.rgb_color, mass, oBlob2.mass);            
    RGBColor::toHSV (rgb_color, hsv_color);

    // union of windows
    window = window | oBlob2.window;       // equivalent to cvMaxRect
    mass += oBlob2.mass;
}

void Blob::updateBlob(Blob& oBlob2)
{
    *this = oBlob2;
}
}
