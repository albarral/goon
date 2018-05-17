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

    // Performs a matching process between an object model and a list of object models.
    // In default mode (bappend = false) the list of candidates is reset in each call.
    // In append mode (bappend = true) the new candidates are appended to the existing candidates list..
    // It returns true if there are matching candidates, false otherwise
    bool doMatching(ObjectModel& oObjectModel, std::vector<ObjectModel>& listObjectModels, bool bappend = false);

    // get access to the sequence of candidate matches.
    std::vector<st_match>& getListCandidateMatches() {return seq_candidate_matches;};

    std::string showCandidates();    
};
}
#endif
