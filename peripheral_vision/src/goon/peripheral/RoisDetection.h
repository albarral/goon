#ifndef __GOON_PERIPHERAL_ROIS_DETECTION_H
#define __GOON_PERIPHERAL_ROIS_DETECTION_H

/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <queue>
#include <chrono>
#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "goon/peripheral/Unit.h"
#include <goon/data/base/region.h>
#include "goon/utils/hsv_color.h"


namespace goon
{
class RoisDetection
{
private:
    static log4cxx::LoggerPtr logger;
    static const int MAX_ID;    
    float MAXDISTXY_SQR;                        // size of the units' receptive fields 
    std::list<Unit> list_units;                 // list of active units
    std::queue<int> seq_available_ids;  // sequence of available IDs (FIFO queue)
    std::list<Unit>::iterator it_Winner;        // iterator to winner unit (in response to a sampled region)
    std::list<Unit>::iterator it_Second;       // iterator to second unit (in response to a sampled region)
    std::chrono::steady_clock::time_point time;   // time point used to compute units movements
    int merges;
    int eliminations;
    HSVColor oHSVColor;

public:
    RoisDetection();
    ~RoisDetection ();
    
    void setSizeReceptiveFields(float value) {MAXDISTXY_SQR = value;};

    // This function prepares all active units for a new sampling process    
    void prepareUnits ();
    
    // Implement a competition among the reception units to respond to the sampled region
    void respond2Region (Region& oRegion);
    
    // This function updates the active units using their response to the last frame sampling.
    // Those units that have not responded to any sample during the last frame are eliminated.
    void updateUnits ();
    
    // Returns a reference to the list of units
    std::list<Unit>& getListUnits () {return list_units;};
        
    void getNumbers (int* merged_units, int* eliminated_units);

private:
    // Checks among the touched units the two nearest to the sampled region that respond to its color													  
    void checkWinners (cv::Vec3f& region_color, int& winner, int& second);
    
    // Tracks the two responding units that are nearest to the sampled region.
    void trackWinner (std::list<Unit>::iterator it_Unit);

    // This function creates a new unit with the given sampled region.
    void generateNewUnit (Region& oRegion) ;

    // Merges the two winner units, with the bigger absorbing the smaller.
    // The absorbed unit is removed from the list of units and its ID is made available for reutilization.
    void mergeUnits ();

};

}  

#endif
