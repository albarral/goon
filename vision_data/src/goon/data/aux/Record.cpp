/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/aux/Record.h"
	
namespace goon 
{
// constructor
Record::Record ()
{
    impact = 0;
    timeFirstStored = timeLastSeen = timeLastUpdate = 0;
    num_seen = 0;
    num_updates = 0;
}

void Record::seen()
{
    num_seen++;
    timeLastSeen = std::time(nullptr);
}

void Record::updated()
{
    num_updates++;    
    timeLastUpdate = std::time(nullptr);  
    // first update means first storage
    if (num_updates == 1)
        timeFirstStored = timeLastUpdate;
}
}
