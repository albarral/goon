/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/highgui/highgui.hpp"  // for imread

#include "goon/camera/models/image_flow.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr ImageFlow::logger(Logger::getLogger("goon.camera"));

ImageFlow::ImageFlow (std::string path)
{        
    address = path;    
    bread = false;
}

ImageFlow::~ImageFlow()
{
}


int ImageFlow::connect() 
{
    int ret = 0;

    image = cv::imread(address);

    if (image.data != NULL) 
    {
        bconnected = true;
        bread = true;
        img_w = image.cols;       
        img_h = image.rows;            
        LOG4CXX_INFO(logger, "connection ok - " << address);
        LOG4CXX_INFO(logger, "capture size = " << img_w << "x" << img_h);
    }
    else
    {
        ret = -1;
        LOG4CXX_ERROR(logger, "connection failed - " << address);
    }
    
    return ret;
}


int ImageFlow::grab() 
{
    int ret = 0;
        
    // just need to read it once, in connect function
    if (!bread) 
    {
        ret = connect();
    }
    else 
    {
        LOG4CXX_TRACE(logger, "frame " << counter);
    }

    counter ++;
    return ret;
}
}