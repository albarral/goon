#ifndef __GOON_MAIN_TEST_H
#define __GOON_MAIN_TEST_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "opencv2/opencv.hpp"
#include "goon/data/retina.h"
#include "goon/data/base/region.h"
#include "goon/data/base/Body.h"

namespace goon
{    
class Test
{
private:
        static log4cxx::LoggerPtr logger;

public:
        //Test();
                
        void testMaskAcces();            
        void testSegmentation();
        
        void showRetina(cv::Mat& imageCam, Retina& oRetina);
        Body getBorderFromRegion(Region& oRegion);
};

}    
#endif
