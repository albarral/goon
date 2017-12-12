#ifndef __GOON_PERIPHERAL_IDPOOL_H
#define __GOON_PERIPHERAL_IDPOOL_H

/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <queue>

namespace goon
{
// Manages a pool of available IDs that can be fetched and freed. 
// It works as a FIFO list, using the oldest of the unused ones.
// On resize() the list is filled with all available IDs.
// On takeOne() the first available ID is fetched (and therefore removed from the list).
// On freeOne() the given ID is made available again being added at the end of the list.    
class IDPool
{
private:
    int MAX_ID;    
    std::queue<int> seqIDs;  // sequence of available IDs (FIFO queue)

public:
    IDPool();
    ~IDPool ();
    
    void refill(int num);
    
    // fetches first available ID (removing it from the list))
    int takeOne();
    
    // frees the given ID (adding it again to the list)
    void freeOne(int ID);

};

}  

#endif
