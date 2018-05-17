#ifndef __GOON_CORTEX_CONFIDENCE2_H
#define __GOON_CORTEX_CONFIDENCE2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/core/core.hpp>
#include <log4cxx/logger.h>
#include "goon/cortex/recognition/matches.h"			
						

namespace goon
{
class Confidence2
{
    private:
        static log4cxx::LoggerPtr logger;
        CvSeq* seq_confident_matches;
        CvMemStorage* storage;
	int numIdentifications;
	int numConfident;
	int numUndefined;
	int numInsufficient;
	int numEmpty;

        // Results of the landmarks recognition processes
    enum eResult{
	eREC_EMPTY,
        eREC_INSUFFICIENT,
        eREC_UNDEFINED,
        eREC_CONFIDENT,
        eREC_SURE,
        eREC_CONFIRMED
        };
        
    public:
        Confidence2();
        ~Confidence2();

        bool findConfidentMatches (CvSeq* seq_candidate_matches);
	// This function searches for confident matches, those with a clear winner and high confidence value. It puts them in seq_confident_matches.
	// The recognition result can be SURE (winner with super confidence), CONFIDENT (winner with good confidence), UNDEFINED (ambiguous winner) or INSUFFICIENT (winner with low confidence).
	// It returns true if there are confident matches, otherwise it returns false.

        int getIdentifiedObject ();
	// This function returns the id of the identified object.

        void getRecognitionStatistics (int result);
	// This function captures statistical information for posterior display

        bool isRecognitionSafe ();
	// This function checks the validity of the identified model.
	// If the landmark was matched partially or matched with low similarity, the model is not safe and should be updated.

private:
	void filterByConfidence2Ratio (CvSeq* seq_lmk_matches);
	// This function filters a landmark's matches by confidence ratio
	// It searches for the first big gap in confidence ratio and takes the nearest group of candidates.

	static int cmpMatchConfidence2 ( const void* a, const void* b, void* userdata);
	// This function sorts matches by confidence in decreasing order

	bool disambiguateConfidents (CvSeq* seq_winner_matches, st_match** pwinner_match);
	// This function disambiguates a recognition when there are multiple winner matches with good confidence values (but below super confidence).
	// The list of winners is analysed in confidence decreasing order until one is found with positive context evidence, then he is declared the winner.
	// If a winner is found true is returned, otherwise false.

	void showMatchesConfidence2 (CvSeq* seq_candidate_matches);
	// This function shows all the matches confidences
	// vs model = quality (self_evidence, context_evidence) confidence

        void showRecognitionStatistics ();
	// This function shows the statistical information of the recognition process

};
}	
#endif
