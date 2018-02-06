#ifndef __GOON_MAIN_TESTOBJECTS_H
#define __GOON_MAIN_TESTOBJECTS_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <log4cxx/logger.h>

#include "goon/data/cortex/Object.h"
#include "goon/features/Body.h"
#include "goon/data/VisualMemory.h"


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
    
    void createObject(Object& oObject, std::vector<Body>& listBodies);
    
    void identifyObject(Object& oObject, VisualMemory& oVisualMemory);        

};

}    
#endif
