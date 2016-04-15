/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/body/BodyUtils.h"

namespace goon 
{
std::vector<st_bodyOverlap> BodyUtils::computeOverlaps(Body oBody, std::vector<Body> listBodies)
{
    std::vector<st_bodyOverlap> listOverlaps;
    float overlap1, overlap2;    
    st_bodyOverlap bodyOverlap;
    int i=0;
    
    for (Body& oBody2 : listBodies)
    {        
        // if bodies overlap, add overlap info to overlaps list
        if (oBody.checkBodyOverlap(oBody2, overlap1, overlap2))
        {            
            bodyOverlap.body2 = i;
            bodyOverlap.overlap1 = overlap1;
            bodyOverlap.overlap2 = overlap2;
            bodyOverlap.mutualOverlap = overlap1 * overlap2;
            listOverlaps.push_back(bodyOverlap);
        }
        i++;
    }            
    
    return listOverlaps;        
}

st_bodyOverlap BodyUtils::getBestOverlap(Body oBody, std::vector<Body> listBodies)
{
    std::vector<st_bodyOverlap> listOverlaps = computeOverlaps(oBody, listBodies);

    // initially best overlap is no overlap
    st_bodyOverlap bestOverlap;
    bestOverlap.body2 = -1;     
    bestOverlap.mutualOverlap = 0.0;     

    // we track the maximum mutual overlap 
    for (st_bodyOverlap& bodyOverlap : listOverlaps)
    {
        if (bodyOverlap.mutualOverlap > bestOverlap.mutualOverlap)
            bestOverlap = bodyOverlap;
    }
    
    return bestOverlap;        
}

}
							 