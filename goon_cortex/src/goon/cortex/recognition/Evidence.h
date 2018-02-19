#ifndef __GOON_CORTEX_EVIDENCE_H
#define __GOON_CORTEX_EVIDENCE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <vector>
#include <log4cxx/logger.h>

#include "goon/cortex/recognition/Compare.h"
#include "goon/cortex/recognition/matches.h"			
#include "goon/data/cortex/ObjectModel.h"

namespace goon
{
// This class performs an evidence behaviour, comparing the object's previous and present appearance in order to check if it's the same object.
class Evidence
{
private:
    static log4cxx::LoggerPtr logger;
    // params
    float sensitivity;       // matching sensitivity [0, 1] 
    // logic
    ObjectModel oObjectModel0;    // last object model
    Compare oCompare;   // class for models comparison
    st_match match;     // match result
    
public:
    Evidence();
    //~Evidence();

    // Compares the given object model with the previous stored model.
    // It returns true if there both models match, or false otherwise
    bool checkSelfEvidence(ObjectModel& oObjectModel);
    
    std::string showResult();        
};
}
#endif
