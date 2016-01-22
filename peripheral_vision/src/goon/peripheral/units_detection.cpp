/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h> 				 

#include "goon/peripheral/units_detection.h"
#include "goon/utils/rgb_color.h"
#include <goon/utils/distance.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr UnitsDetection::logger(Logger::getLogger("goon.peripheral"));

const int UnitsDetection::MAX_ID = 500;

// constructor
UnitsDetection::UnitsDetection ()
{          
    // intialize list of available IDs (first ID = 1)
    for (int i=1; i<=MAX_ID; i++) 
        seq_available_ids.push(i);
}


//destructor
UnitsDetection::~UnitsDetection ()
{
}


// This function prepares all active units for a new sampling process
void UnitsDetection::prepareUnits ()
{	
    LOG4CXX_TRACE(logger, "prepare units ...");
    
    std::list<Unit>::iterator it_Unit;
    for (it_Unit = list_units.begin(); it_Unit != list_units.end(); it_Unit++)
        it_Unit->prepare();

    merges = 0;
    eliminations = 0;
}


// Implement a competition among the reception units to respond to the sampled region
void UnitsDetection::respond2Region (Region& oRegion)
{
    float HSV_SAME = oHSVColor.getDistSameColor();
    float RGB_SIMILAR = RGBColor::getSqrSimilarDist();

    LOG4CXX_TRACE(logger, "check region " << oRegion.getID());
    
    std::list<Unit>::iterator it_Unit;
    it_Winner = list_units.end();
    it_Second = list_units.end();

    // check the response of all units to the sampled region
    for (it_Unit = list_units.begin(); it_Unit != list_units.end(); it_Unit++)
    {
        it_Unit->computeDistance(oRegion.getPos());

        // if unit responds spatially -> check if it also responds to color
        if (it_Unit->getDistance() < MAXDISTXY_SQR)
        {
            if (oHSVColor.getDistance (oRegion.getHSV(), it_Unit->getHSV(), HSVColor::eSAME_COLOR) < HSV_SAME)
            {
                LOG4CXX_TRACE(logger, "touched unit " << it_Unit->getID());
                // track the two nearest responding units 
                trackWinner (it_Unit);
            }
        }
    }
        
    // update the WINNER unit, and merge it with the second if necessary
    if (it_Winner != list_units.end())
    {
        LOG4CXX_TRACE(logger, "winner = " << it_Winner->getID());

        // Merge two units if one of them responds to the other in xy_space and color_space
        if (it_Second != list_units.end())
        {			
            if (Distance::getEuclidean3s (it_Winner->getRGB(), it_Second->getRGB()) < RGB_SIMILAR)
            {
                mergeUnits();
            }
        }

        // update the winner unit with the sampled region
        it_Winner->addRegion(oRegion.getID(), oRegion);
    }      
    // or CREATE a new unit if no winner was found
    else 
    {
        LOG4CXX_TRACE(logger, "no response");
        generateNewUnit (oRegion);
    }
}
													  

void UnitsDetection::trackWinner(std::list<Unit>::iterator it_Unit)
{
    // if no previous winner OR smallest distance -> new winner
    if (it_Winner == list_units.end() || it_Unit->getDistance() < it_Winner->getDistance())
    {
        it_Second = it_Winner;
        it_Winner = it_Unit;
    }
    // if no previous second OR second smallest distance -> new second
    else if (it_Second == list_units.end() || it_Unit->getDistance() < it_Second->getDistance())                             
        it_Second = it_Unit;   
}


// This function updates the active units using their response to the last frame sampling.
// Those units that have not responded to any sample during the last frame are eliminated.
// The function returns the number of active units.
void UnitsDetection::updateUnits ()
{
    LOG4CXX_TRACE(logger, "update units ...");
    
    std::list<Unit>::iterator it_Unit = list_units.begin();
    
    while (it_Unit != list_units.end())
    {
        LOG4CXX_TRACE(logger, "update unit " << it_Unit->getID());
        it_Unit->update();
        
        // if unit obsolete, remove it from list
        if (it_Unit->getMass() == 0)
        {       
            LOG4CXX_TRACE(logger, "eliminate !!!" << it_Unit->getID());
            // its id is available again
            seq_available_ids.push(it_Unit->getID());
            // erase function returns the next item in the list
            it_Unit = list_units.erase(it_Unit);
            
            eliminations++;
        }
        else             
            it_Unit++;        
    }
}


void UnitsDetection::getNumbers (int* merged_units, int* eliminated_units)
{
    *merged_units = merges;
    *eliminated_units = eliminations;
}


// This function creates a new unit with the given sampled region.
void UnitsDetection::generateNewUnit (Region& oRegion)
{
    int ID; 
    
    // if IDs available, create a new unit
    if (!seq_available_ids.empty())				
    {
        ID = seq_available_ids.front();
        seq_available_ids.pop();
            
        LOG4CXX_TRACE(logger, "new unit > " << ID);

        Unit oUnit; // new unit created
        oUnit.setID(ID);
        oUnit.initialize(oRegion.getID(), oRegion);
        
        list_units.push_back(oUnit);
    }
    else
        LOG4CXX_WARN (logger, "Unit creation ignored -> no IDs available");		
}


void UnitsDetection::mergeUnits ()
{
    int predator, prey;
   
    // second is absorbed (and deleted from list)
    if (it_Winner->getMass() >= it_Second->getMass())
    {
        predator = it_Winner->getID();
        prey = it_Second->getID();
                
        it_Winner->absorb(*it_Second);
        list_units.erase(it_Second);        
    }
    // winner is absorbed (and deleted from list)
    else
    {		
        prey = it_Winner->getID();
        predator = it_Second->getID();

        it_Second->absorb(*it_Winner);
        list_units.erase(it_Winner);
        // second becomes winner (for later update)
        it_Winner = it_Second;
    }

    LOG4CXX_TRACE(logger, prey << " absorbed -> " << predator);
    // the absorbed id is available again
    seq_available_ids.push(prey);

    merges++;
}

}




