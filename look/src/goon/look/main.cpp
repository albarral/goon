/***************************************************************************
 *   Copyright (C) 2017 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include <vector>
#include <string>
#include <unistd.h> // for sleep() 

#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>

#include "goon/look/GoonControl.h"

using namespace goon;

void runGoon();
// obtains user's home path
std::string getHomePath();

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("goon.main"));

// main program
int main(int argc, char** argv) 
{
//    std::string home = getHomePath();
//    std::string configFile = home + "/.tron/log4cxx_config_body.xml";
//    log4cxx::xml::DOMConfigurator::configure(configFile);    
    log4cxx::xml::DOMConfigurator::configure("log4cxx_config.xml");
        
    LOG4CXX_INFO(logger, "\n\nSTART goon\n");

    runGoon();
      
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
        //while (!oGoonControl.checkEndRequested()) 
        while (seconds < 10) 
        {
//            oGoonTest.testArtistic();

            sleep(1);       
            seconds++;
        }    

        LOG4CXX_INFO(logger, "\ngoon end requested ...\n");
        oGoonControl.end();        
    }
    else
        LOG4CXX_ERROR(logger, "GoonControl could not be launched");
        
    return;
}

std::string getHomePath()
{    
    // obtain value of HOME environment variable
    char* pVar = getenv("HOME");    
    if (pVar!=NULL)
    {
        // transform it in a string
        std::string home(pVar);
        return home;
    }
    else
        return "";
}
