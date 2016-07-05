/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
#include <iostream> 
#include "goon/data/base/BodyUtils.h"

namespace goon 
{
std::vector<st_bodyOverlap> BodyUtils::computeOverlaps(Body oBody, std::vector<Body> listBodies)
{
    int i=0, pixelsShared;
    st_bodyOverlap bodyOverlap;
    std::vector<st_bodyOverlap> listOverlaps;
    
    for (Body& oBody2 : listBodies)
    {               
        // if bodies overlap, add overlap info to overlaps list
        pixelsShared = oBody.computeOverlap(oBody2);
        if (pixelsShared > 0)
        {            
            bodyOverlap.body2 = i;
            bodyOverlap.overlap1 = (float)pixelsShared / oBody.getMass();
            bodyOverlap.overlap2 = (float)pixelsShared / oBody2.getMass();
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
    bestOverlap.overlap1 = bestOverlap.overlap2 =0.0;     
    float mutualOverlap, maxOverlap = 0.0;

    // we track the maximum mutual overlap 
    for (st_bodyOverlap& bodyOverlap : listOverlaps)
    {
        mutualOverlap = bodyOverlap.overlap1 * bodyOverlap.overlap2;
        //std::cout << "getBestOverlap: " << bodyOverlap.body2 << " - " << bodyOverlap.overlap1 << ", " << bodyOverlap.overlap2 << ", " << mutualOverlap  << std::endl;
        if (mutualOverlap > maxOverlap)
        {
            //std::cout << "it's best" << std::endl;
            bestOverlap = bodyOverlap;
        }
    }
    
    return bestOverlap;        
}

}
							 