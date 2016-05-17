/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/peripheral/IDPool.h"

namespace goon
{
IDPool::IDPool ()
{          
    refill(500);
}

IDPool::~IDPool ()
{
    // first, clear list
    while (!seqIDs.empty())
        seqIDs.pop();
}


void IDPool::refill(int num)
{	
    MAX_ID = num;
    
    // first, clear list
    while (!seqIDs.empty())
        seqIDs.pop();
    
    // initialize list of available IDs (first ID = 1)
    for (int i=1; i<=MAX_ID; i++) 
        seqIDs.push(i);
}


int IDPool::takeOne()
{
    int ID = seqIDs.front();
    seqIDs.pop();
    return ID;
}
													  

void IDPool::freeOne(int ID)
{
    seqIDs.push(ID);
}

}




