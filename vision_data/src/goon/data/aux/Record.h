#ifndef __GOON_DATA_RECORD_H
#define __GOON_DATA_RECORD_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <ctime>
#include <chrono> 

namespace goon 
{
// This class represents the history of an object's model.
// It holds info such as: impact, first time stored, times seen, times updated ...
 class Record
{     
 protected:
     int impact;
    //chrono::time_point<std::chrono::system_clock> timeFirstStored;    // available in c++11 version (not fully installed yet)
    //chrono::time_point<std::chrono::system_clock> timeLastSeen;
    //chrono::time_point<std::chrono::system_clock> timeLastUpdate;   
     std::time_t timeFirstStored;
     std::time_t timeLastSeen;
     std::time_t timeLastUpdate;
     int num_seen;
     int num_updates;
//     float frequency;

 public:
     Record ();
     //~Record();

    std::time_t getTimeFirstStored() {return timeFirstStored;};

    void seen();
    int getNumSeen() {return num_seen;};
    std::time_t getTimeLastSeen() {return timeLastSeen;};

    void updated();
    int getNumUpdates() {return num_updates;};
    std::time_t getTimeLastUpdate() {return timeLastUpdate;};  
    
    int getImpact() {return impact;};    
    void setImpact(int impact) {this->impact=impact;};    
};  
}  
#endif
