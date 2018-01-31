#ifndef __GOON_MAIN_TESTBODIES_H
#define __GOON_MAIN_TESTBODIES_H

/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"

namespace goon
{    
class TestBodies
{
private:

public:
        //TestBodies();                
        void test();              
        
private:
    int getBestOverlap(std::vector<cv::Vec2f> listOverlaps);
};

}    
#endif
