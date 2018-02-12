#ifndef __GOON_CORTEX_MATCHING2_H
#define __GOON_CORTEX_MATCHING2_H

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
// This class performs appearance based comparisons between objects and models.
// The quality of the matchings is used to filter the real matching candidates.
class Matching2
{
private:
    static log4cxx::LoggerPtr logger;
    // params
    float sensitivity;       // matching sensitivity [0, 1] affects the matching qualities required to accept matchings
    // logic
    Compare oCompare;   // class for models comparison
    std::vector<st_match> seq_candidate_matches;    // list of candidate matches
    
public:
    Matching2();
    //~Matching2();

    // performs a matching process between an object model and a list of object models.
    // It returns true if there are matching candidates, false otherwise
    bool doMatching(ObjectModel& oObjectModel, std::vector<ObjectModel>& listObjectModels);

    // get access to the sequence of candidate matches.
    std::vector<st_match>& getListCandidateMatches() {return seq_candidate_matches;};

    std::string showCandidates();

private:
    // selects best candidate matches from the given list
    //void filterCandidates();
    
};
}
#endif
