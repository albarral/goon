#ifndef __GOON_MAIN_TESTOBJECTS_H
#define __GOON_MAIN_TESTOBJECTS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

namespace goon
{    
class TestObjects
{
private:
    static log4cxx::LoggerPtr logger;
    
public:
        //TestObjects();                
        void test();                      
};

}    
#endif
