/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "goon/cortex/recognition/Matching2.h"
							
using namespace log4cxx;

namespace goon
{
LoggerPtr Matching2::logger(Logger::getLogger("goon.cortex.recognition"));

// Constructor
Matching2::Matching2()
{
    sensitivity = 0.5;
}

//Matching2::~Matching2 ()
//{
//}


bool Matching2::doMatching(ObjectModel& oObjectModel, std::vector<ObjectModel>& listObjectModels, bool bappend)
{
    LOG4CXX_TRACE(logger, "Matching2.doMatching");
    
    // in default mode, clear candidates list
    if (!bappend)
        seq_candidate_matches.clear();

    st_match match;					
    
    // for each candidate model 
    for (ObjectModel& oObjectModel2 : listObjectModels)
    {		
        LOG4CXX_DEBUG(logger, "Matching2: object vs model " << oObjectModel2.getID());
        // compare object model and candidate model
        float quality = oCompare.compareObjectModels(oObjectModel, oObjectModel2);        
        float maxQuality = oCompare.getMaxPossibleQuality();

        LOG4CXX_DEBUG(logger, "Matching2: " << oCompare.showCorrespondences());
        LOG4CXX_DEBUG(logger, "Matching2: quality = " + std::to_string(quality) + ", max quality = " + std::to_string(maxQuality));
        
        // if matching quality is high enough, add new match candidate 
        if (quality >= sensitivity*maxQuality)
        {                
            match.modelID = oObjectModel2.getID();
            match.quality = quality;
            match.objectMatchedFraction = oCompare.getMatchedFration1();
            match.modelMatchedFraction = oCompare.getMatchedFration2();

            seq_candidate_matches.push_back(match);                        
        }
    } 

    return (!seq_candidate_matches.empty());
}

std::string Matching2::showCandidates()
{
    std::string text = "matching candidates = " +  std::to_string(seq_candidate_matches.size()) + "\n";
    for (st_match& match : seq_candidate_matches)
    {
        text += "model " + std::to_string(match.modelID)          
                + ": quality = " + std::to_string(match.quality)
                + ", object matched fraction = " + std::to_string(match.objectMatchedFraction)
                + ", model matched fraction = " + std::to_string(match.modelMatchedFraction) + "\n";
    }
    return text;
}

}
