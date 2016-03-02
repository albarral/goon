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

void Blob::setCovariances (float covx, float covy, float covxy) {covs[0] = covx; covs[1] = covy; covs[2] = covxy;}


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

std::string Blob::toString()
{
    std::string desc = "Blob [mass = " + std::to_string(mass) +
            ", pos = (" + std::to_string(pos[0]) + "," + std::to_string(pos[1]) + ")" +
            ", covs = (" + std::to_string((int)covs[0]) + "," + std::to_string((int)covs[1]) + "," + std::to_string((int)covs[2]) + ")" +
            ", rgb = (" + std::to_string((int)rgb_color[0]) + "," + std::to_string((int)rgb_color[1]) + "," + std::to_string((int)rgb_color[2]) + ")" +
            ", hsv = (" + std::to_string((int)hsv_color[0]) + "," + std::to_string((int)hsv_color[1]) + "," + std::to_string((int)hsv_color[2]) + ")" +
            ", window = (" + std::to_string(window.x) + "," + std::to_string(window.y) + "," + std::to_string(window.width) + "," + std::to_string(window.height) + ")" +
            "]";
    return desc;
}
}
