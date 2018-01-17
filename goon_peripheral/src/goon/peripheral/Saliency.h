#ifndef __GOON_PERIPHERAL_SALIENCY_H
#define __GOON_PERIPHERAL_SALIENCY_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <vector>
#include <log4cxx/logger.h>

#include "goon/data/base/roi.h"

namespace goon 
{
// salient structure (used to compute saliency)
struct stSalient
{
    int roiID;
    float difSat;
    float difValue;
    float difSpeed;            
    float saliency;
};
    
class Saliency
{    
public:    
    enum eMode
    {
        eSALIENCY_COLOR,            // color saliency mode
        eSALIENCY_MOVEMENT,      // movement saliency mode
        eSALIENCY_DUAL,               // dual saliency mode (color + movement)
        eSALIENCY_DIM
    };
   
private:
    static log4cxx::LoggerPtr logger;
    int mode;
    float avgSat;       // average hsv saturation
    float avgValue;       // average hsv value
    float avgSpeed;  // average ROI speed
    std::vector<stSalient> listSalients;    // list of salient ROIs ordered by saliency

public:
    Saliency();
    ~Saliency();
    
    void setMode(int value);
    int getMode() {return mode;}    
    std::vector<stSalient>& getListSalients();;
    
    // computes the saliency of all given ROI's
    void computeSaliency(std::list<ROI>& listROIs);

    // sorts the salient list by decreasing saliency value
    //void sortBySaliency();

    stSalient& getMostSalient();
    
    static std::string toString(stSalient& salient);
    
private: 
    // compute saliency of given salient 
    float computeSaliency(stSalient& salient);

};
}    
#endif
