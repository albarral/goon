/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
		
#include <stdio.h>
		
#include "goon/cortex/recognition/confidence.h"			
#include "goon/cortex/config/recognition_defines.h"

using namespace log4cxx;
namespace goon
{
LoggerPtr Confidence::logger(Logger::getLogger("goon.cortex.recognition.confidence"));

#define SHOW_STATISTICAL_INFO

// Constructor
Confidence::Confidence ()
{
    storage = cvCreateMemStorage(0);

    seq_confident_matches = cvCreateSeq (CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_match), storage);

    numIdentifications = numConfident = numUndefined = numInsufficient = numEmpty = 0;

    LOG4CXX_INFO(logger, "parameters: (good confidence, super confidence, confidence ratio) = (" << GOOD_CONFIDENCE << ", " << SUPER_CONFIDENCE << ", " << SAFE_CONFIDENCE_RATIO);
    LOG4CXX_INFO(logger, "shown info -> quality (self evidence, context evidence) confidence");
}


// Destructor
Confidence::~Confidence ()
{
	cvReleaseMemStorage (&storage );

	showRecognitionStatistics ();
}



// This function searches for confident matches, those with a clear winner and high confidence value. It puts them in seq_confident_matches.
// The recognition result can be SURE (winner with super confidence), CONFIDENT (winner with good confidence), UNDEFINED (ambiguous winner) or INSUFFICIENT (winner with low confidence).
// It returns true if there are confident matches, otherwise it returns false.
bool Confidence::findConfidentMatches (CvSeq* seq_candidate_matches)
{
#ifdef DEBUG_MODE
	cout << " init - FindConfidentMatches" << endl;
#endif
	int result;
	st_match *best_match;
	st_match* second_match;
	st_match* winner_match;
	
	showMatchesConfidence (seq_candidate_matches);

	cvClearSeq (seq_confident_matches);
							
	// if several candidates, get match winners 
	if (seq_candidate_matches->total > 1)
	{		
		filterByConfidenceRatio (seq_candidate_matches);
	}

	// check filtered matches
	switch (seq_candidate_matches->total)
	{
            // no candidates
            case 0:

                    result = eREC_EMPTY;

                    break;

            // unique candidate
            case 1:

                    best_match = (st_match*)cvGetSeqElem (seq_candidate_matches, 0);

                    if (best_match->confidence < GOOD_CONFIDENCE)
                    {
                            result = eREC_INSUFFICIENT;
                    }
                    else if (best_match->confidence < SUPER_CONFIDENCE)
                    {
                            result = eREC_CONFIDENT;
                    }
                    else
                            result = eREC_SURE;

                    break;

            // various candidates
            default:

                    best_match = (st_match*)cvGetSeqElem (seq_candidate_matches, 0);
                    second_match = (st_match*)cvGetSeqElem (seq_candidate_matches, 1);

                    if (best_match->confidence < GOOD_CONFIDENCE)
                    {
                            result = eREC_INSUFFICIENT;
                    }
                    else if (best_match->confidence < SUPER_CONFIDENCE)
                    {
                            if (second_match->confidence < GOOD_CONFIDENCE)
                            {
                                    result = eREC_CONFIDENT;
                            }
                            else if (disambiguateConfidents (seq_candidate_matches, &winner_match))
                            {
                                    result = eREC_CONFIDENT;
                                    best_match = winner_match;
                            }
                            else
                                    result = eREC_UNDEFINED;
                    }
                    else
                            result = eREC_SURE;
                    break;
	}

        #ifdef  SHOW_STATISTICAL_INFO
	getRecognitionStatistics (result);
        #endif

	// store confident and sure matches
	if (result >= eREC_CONFIDENT)
	{
            cvSeqPush (seq_confident_matches, best_match);

            LOG4CXX_INFO(logger, "      matched -> " << best_match->matched_object);
	} 
									  			
#ifdef DEBUG_MODE
	cout << " end - FindConfidentMatches" << endl;
#endif  
	return (result >= eREC_CONFIDENT);
}



// This function filters a landmark's matches by confidence ratio
// It searches for the first big gap in confidence ratio and takes the nearest group of candidates.  
void Confidence::filterByConfidenceRatio (CvSeq* seq_lmk_matches)
{	
#ifdef DEBUG_MODE
	cout << " init - FilterByConfidenceRatio" << endl;	
#endif
	st_match match;
	st_match *match1, *match2;
	int nearest_group;
	
	// sort matches by confidence in decreasing order
	cvSeqSort (seq_lmk_matches, cmpMatchConfidence, 0);
	
	// find gap in confidence ratio
	nearest_group = seq_lmk_matches->total;
	match1 = (st_match*)cvGetSeqElem (seq_lmk_matches, 0);		
	for (int i=1; i < seq_lmk_matches->total; i++)
	{
		match2 = (st_match*)cvGetSeqElem (seq_lmk_matches, i);		
				
		if (match1->confidence / match2->confidence > SAFE_CONFIDENCE_RATIO)
		{
			nearest_group = i;
			break;
		}
		match1 = match2;
	}
		
	// filter the first group of matches
	while (seq_lmk_matches->total > nearest_group)
	{
		cvSeqPop (seq_lmk_matches, &match);		
	}			
					
#ifdef DEBUG_MODE
	cout << " end - FilterByConfidenceRatio" << endl;	
#endif
}



// This function sorts matches by confidence in decreasing order
int Confidence::cmpMatchConfidence ( const void* a, const void* b, void* userdata)
{
	st_match* match_a = (st_match*)a;
	st_match* match_b = (st_match*)b;

	return (match_b->confidence - match_a->confidence);
}



// This function disambiguates a recognition when there are multiple winner matches with good confidence values (but below super confidence).
// The list of winners is analysed in confidence decreasing order until one is found with positive context evidence, then he is declared the winner. 
// If a winner is found true is returned, otherwise false.
bool Confidence::disambiguateConfidents (CvSeq* seq_winner_matches, st_match** pwinner_match)
{
#ifdef DEBUG_MODE
	cout << " init - DisambiguateConfidents" << endl;
#endif
	bool bwinner_found = false;
	st_match* match;
	
	for (int i=0; i < seq_winner_matches->total; i++)
	{
		match = (st_match*)cvGetSeqElem (seq_winner_matches, i);		
				
		if (match->confidence > GOOD_CONFIDENCE && match->context_evidence > 0)
		{
			bwinner_found = true;
			*pwinner_match = match;
			break;
		}
	}

	return (bwinner_found);
			  
#ifdef DEBUG_MODE
	cout << " end - DisambiguateConfidents" << endl;
#endif  
}



// This function shows all the matches confidences
// vs model = quality (self_evidence, context_evidence) confidence
void Confidence::showMatchesConfidence (CvSeq* seq_candidate_matches)
{
#ifdef DEBUG_MODE
	cout << " init - ShowMatchesConfidence" << endl;
#endif
	st_match *match;

        LOG4CXX_DEBUG(logger, "Confidence ...");
	for (int j=0; j < seq_candidate_matches->total; j++)
	{
            match = (st_match*)cvGetSeqElem (seq_candidate_matches, j);

            LOG4CXX_DEBUG(logger, "        vs. model " << match->matched_object << "." << match->matched_view);
            LOG4CXX_DEBUG(logger, "= " << match->quality << " (" << match->self_evidence << ", " << match->context_evidence << ") " << match->confidence);
	}		
	  
#ifdef DEBUG_MODE
	cout << " end - ShowMatchesConfidence" << endl;
#endif  
}



// This function returns the id of the identified object.
int Confidence::getIdentifiedObject ()
{
	st_match *match;
		
	match = (st_match*)cvGetSeqElem (seq_confident_matches, 0);
	   
	return (match->matched_object);
}



// This function captures statistical information for posterior display
void Confidence::getRecognitionStatistics (int result)
{
#ifdef DEBUG_MODE
	cout << " init - GetRecognitionStatistics" << endl;
#endif
			
	numIdentifications ++;
	
	switch (result)
	{
		case 	eREC_EMPTY:
			numEmpty ++;
			break;
		case 	eREC_INSUFFICIENT:
			numInsufficient ++;
			break;
		case 	eREC_UNDEFINED:
			numUndefined ++;
			break;
		case 	eREC_CONFIDENT:
		case 	eREC_SURE:
		case 	eREC_CONFIRMED:
			numConfident ++;
			break;
	}
		
#ifdef DEBUG_MODE
	cout << " end - GetRecognitionStatistics" << endl;
#endif
}


// This function checks the validity of the identified model. 
// If the landmark was matched partially or matched with low similarity, the model is not safe and should be updated.
bool Confidence::isRecognitionSafe ()
{
	bool bsafe;
	st_match *match;	
		
	match = (st_match*)cvGetSeqElem (seq_confident_matches, 0);

	if (match->lmk_matched_weight < SAFE_RECOGNITION_WEIGHT || match->lowest_similarity < (SIMILARITY + SIMILARITY_MARGIN))
		bsafe = false;							
	else
		bsafe = true;
	
	return (bsafe);
}


// This function shows the statistical information of the recognition process
void Confidence::showRecognitionStatistics ()
{
#ifdef DEBUG_MODE
	cout << " init - ShowRecognitionStatistics" << endl;
#endif

        LOG4CXX_INFO(logger, "RECOGNITION STATISTICS:");
	LOG4CXX_INFO(logger, "total identifications = " << numIdentifications);
	LOG4CXX_INFO(logger, "confident matches = " << numConfident);
	LOG4CXX_INFO(logger, "undefined matches = " << numUndefined);
	LOG4CXX_INFO(logger, "insufficient matches = " << numInsufficient);
	LOG4CXX_INFO(logger, "empty matches = " << numEmpty);
		
#ifdef DEBUG_MODE
	cout << " end - ShowRecognitionStatistics" << endl;
#endif
}
}

