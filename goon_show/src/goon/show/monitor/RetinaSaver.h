#ifndef __GOON_SHOW_RETINASAVER_H
#define __GOON_SHOW_RETINASAVER_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <list>
#include "opencv2/core/core.hpp"

#include "tivy/Draw.h"
#include "goon/data/base/Body.h"
#include "goon/data/base/region.h"

namespace goon 
{
class RetinaSaver
{    
public:    
   
private:
    tivy::Draw oDraw;
    std::string path;
    std::string imgExtension;


public:
    RetinaSaver();
//    ~RetinaSaver();
    
    void setDestinationFolder(std::string path);
    
    // saves an image for each region in the given list
    void saveRegions (cv::Mat& image_cam, std::list<Region>& listRegions);
    
    // saves an image of the given body (and sets the given name)
    void saveBody(cv::Mat& imageCam, Body& oBody, cv::Vec3f& color, std::string name, int ID);    
};
}    
#endif
