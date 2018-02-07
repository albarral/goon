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
    reqQuality = 100;    
}

//Matching2::~Matching2 ()
//{
//}


// This function performs a matching process between the specified landmark & the database models 
// It returns true if there are matching candidates, otherwise it returns false.		
bool Matching2::doMatching(Object& oObject, std::vector<ObjectModel>& listObjectModels)
{
    LOG4CXX_TRACE(logger, "Matching2.doMatching");
    
    seq_candidate_matches.clear();
    st_match match;					
	
    ObjectModel oObjectModel;
    oModeling.modelObject(oObject, oObjectModel);
    
    // for each model
    for (ObjectModel& oObjectModel2 : listObjectModels)
    {		
        // compare object and model
        float quality = oCompare.compareObjectModels(oObjectModel, oObjectModel2);
        
        // if matching quality is high enough, add new match candidate 
        if (quality >= reqQuality)
        {                
            match.modelID = oObjectModel2.getID();
            match.quality = quality;
            match.objectMatchedFraction = oCompare.getMatchedFration1();
            match.modelMatchedFraction = oCompare.getMatchedFration2();

            seq_candidate_matches.push_back(match);
        }
    } 

    // if various candidates -> filter the best 
//    if (seq_candidate_matches.size() > 1)
//        filterCandidates();

    LOG4CXX_DEBUG(logger, "best_candidates = " << seq_candidate_matches.size());

    return (!seq_candidate_matches.empty());
}

//
//void Matching2::filterCandidates(std::vector<st_match>& seq_matches)
//{	
//    LOG4CXX_TRACE(logger, "Matching2.filterCandidates");
//
//    CvSeq* seq_candidates = cvCreateSeq( CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_candidate), storage);
//	st_candidate *candidate;
//	st_candidate new_candidate;
//	st_match *match;
//	int matched_object;
//	bool bcandidate_found;
//
//	// FIND WINNER VIEWS OF BEST CANDIDATE OBJECTS
//	
//	// for each candidate match
//	for (int i=0; i < seq_matches->total; i++)
//	{
//		match = (st_match*)cvGetSeqElem (seq_matches, i);		
//		
//		matched_object = match->modelID;
//		
//		// check if matched object is already a candidate
//		bcandidate_found = false;
//		for (int j=0; j < seq_candidates->total; j++)
//		{
//			candidate = (st_candidate*)cvGetSeqElem (seq_candidates, j);		
//			
//			if (matched_object == candidate->object)
//			{
//				bcandidate_found = true;
//				break;
//			}
//		}
//		
//		// if matched object was a candidate
//		if (bcandidate_found)
//		{	
//			// update it only if new view was better matched
//			if (match->quality > candidate->quality)
//			{
//				candidate->quality = match->quality;
//				candidate->match_position = i;
//			}
//		}
//		// otherwise add it as new candidate
//		else
//		{
//			new_candidate.object = matched_object;
//			new_candidate.quality = match->quality;
//			new_candidate.match_position = i;
//			
//			cvSeqPush (seq_candidates, &new_candidate);
//		}		
//	}	// end for
//		
//	// Put the winner views in seq_candidate_matches	
//	for (int k=0; k < seq_candidates->total; k++)
//	{
//		candidate = (st_candidate*)cvGetSeqElem (seq_candidates, k);		
//
//		match = (st_match*)cvGetSeqElem (seq_matches, candidate->match_position);		
//				
//		cvSeqPush (seq_candidate_matches, match); 	
//	}	
//		
//	cvClearSeq (seq_candidates);
//		
//#ifdef DEBUG_MODE
//	cout << " end - GetBestCandidates" << endl;	
//#endif
//}

}
