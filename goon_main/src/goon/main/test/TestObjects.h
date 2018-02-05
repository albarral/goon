#ifndef __GOON_MAIN_TESTOBJECTS_H
#define __GOON_MAIN_TESTOBJECTS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "goon/features/Body.h"


namespace goon
{    
class TestObjects
{
private:
    static log4cxx::LoggerPtr logger;
    
public:
        //TestObjects();                
        void test();                      
        
private:
    void createBodies(std::vector<Body>& listBodies);
    
    void createObject(std::vector<Body>& listBodies);

};

}    
#endif
