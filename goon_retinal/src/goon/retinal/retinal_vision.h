#ifndef __GOON_RETINAL_VISION_H
#define __GOON_RETINAL_VISION_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"
#include <log4cxx/logger.h>

#include <goon/data/retina.h>
#include "goon/retinal/segmentation.h"
#include "goon/retinal/merge.h"

namespace goon
{
class RetinalVision
{
private:
        static log4cxx::LoggerPtr logger;
        Retina oRetina;
        Segmentation4 oSegmentation4;
        Merge oMerge;

public:
    RetinalVision();
    ~RetinalVision();

    Retina& getRetina() {return oRetina;};

    /// Initializes the module adapting it to the image size
    void init(int img_w, int img_h);
    
    // Changes the main parameters of the retinal vision system.
    void setParameters(int retinal_samples, int same_RGB, int similar_RGB);

    void update(cv::Mat& image_cam);
    // This function performs the retinal vision process.
    // It detects homogenous color regions in the captured image which will be later used by higher vision processes.

private:    
    // logs a short description of all extracted regions
    void describeRegions ();
};

}  

#endif
