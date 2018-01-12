/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "goon/main/GoonControl.h"
#include "goon/main/test/TestBodies.h"
#include "goon/main/test/TestRegions.h"
#include "goon/main/test/Test.h"
//#include "tuly/utils/Environment.h"

using namespace goon;

void runGoon();
void oneShotTest();
int test();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("goon.main"));

// main program
int main(int argc, char** argv) 
{
//    std::string configFile = tuly::Environment::getHomePath() + "/.tron/log4cxx_config_body.xml";
//    log4cxx::xml::DOMConfigurator::configure(configFile);    
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
        
    LOG4CXX_INFO(logger, "\n\nSTART goon\n");

    //runGoon();
    //oneShotTest();
    test();
      
    return 0;
}

// runs the body control
void runGoon()
{        
    GoonControl oGoonControl; 

    // TEST SECTION
//    GoonTest oGoonTest;
//    oGoonTest.connect2Bus(oGoonControl.getGoonBus4Test());

    // launch goon control & wait for it to end            
    if (oGoonControl.launch())
    {    
        int seconds = 0;
        while (!oGoonControl.checkEndRequested()) 
        {
            sleep(1);       
            seconds++;
        }    

        LOG4CXX_INFO(logger, "goon end requested ...\n");
        oGoonControl.end();        
    }
    else
        LOG4CXX_ERROR(logger, "GoonControl could not be launched");
        
    return;
}

void oneShotTest() 
{        
    LOG4CXX_INFO(logger, "\n\nONE SHOT TEST goon VISION ...\n");

    GoonControl oGoonControl; 
    oGoonControl.oneShot();

    LOG4CXX_INFO(logger, "END of test ...");
}

int test()
{
//    goon::TestBodies oTestBodies;
//    oTestBodies.test();
    
    //goon::TestRegions oTestRegions;
    //oTestRegions.testMerge();

    goon::Test oTest;
    oTest.testSegmentation();

    return 0;
}