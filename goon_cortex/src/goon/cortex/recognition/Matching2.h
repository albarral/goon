#ifndef __GOON_CORTEX_MATCHING2_H
#define __GOON_CORTEX_MATCHING2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <vector>
#include <log4cxx/logger.h>

#include "goon/cortex/recognition/Compare.h"
#include "goon/cortex/recognition/Modeling.h"
#include "goon/cortex/recognition/matches.h"			
#include "goon/data/cortex/Object.h"
#include "goon/data/cortex/ObjectModel.h"

namespace goon
{
// This class performs appearance based comparisons between objects and models.
// The quality of the matchings is used to filter the real matching candidates.
class Matching2
{
private:
    static log4cxx::LoggerPtr logger;
    // params
    float reqQuality;       // minimum required quality to consider a feasible matching
    // logic
    Modeling oModeling;     // class for modeling objects
    Compare oCompare;   // class for models comparison
    std::vector<st_match> seq_candidate_matches;    // list of candidate matches
    
public:
    Matching2();
    //~Matching2();

    // Performs a matching process between the given object and the given list of object models.
    // It returns true if there are matching candidates, false otherwise
    bool doMatching(Object& oObject, std::vector<ObjectModel>& listObjectModels);

    // get access to the sequence of candidate matches.
    std::vector<st_match>& getListCandidateMatches() {return seq_candidate_matches;};

private:
    // selects best candidate matches from the given list
    //void filterCandidates();
};
}
#endif
