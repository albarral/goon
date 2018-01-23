#ifndef __GOON_FEATURES_STRUCTURE_H
#define __GOON_FEATURES_STRUCTURE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <vector>
#include "opencv2/core/core.hpp"

 namespace goon
{
class Structure
{
public: 
    enum eNeighbour
    {
        eNEIB_ID,
        eNEIB_RELATIVE_MODULE,
        eNEIB_RELATIVE_ANGLE,
        eNEIB_RELATIVE_WEIGHT,
        eNEIB_DIM
    };
 private:
        cv::Mat matNeighbours;		// neighbours matrix (relation among elements) of depth 4 

 public:
     Structure();
     //~Structure();
     
    // copy constructor (needed for mask)
    Structure(const Structure& oStructure);  
    // assignment operator (needed for mask)
    Structure& operator=(const Structure& oStructure);
     
    cv::Mat& getMatNeighbours() {return matNeighbours;};

    // resize structure to given number of elements
     void resize(int numElements);
    // get neighbours of specified element
    std::vector<cv::Vec4f> getNeighbours(int element);
    // store neighbours of specified element
    void setNeighbours(int element, std::vector<cv::Vec4f>& listNeighbours);
    // clear neighbours of specified element
    void clearNeighbours(int element);
    
    // clear whole structure
    void clear();
};  
}
  
#endif
