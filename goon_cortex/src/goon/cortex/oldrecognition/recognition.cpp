/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>

#include "recognition.h"

namespace goon
{
// Constructor
Recognition::Recognition (VisualCenter* oVisualCenter, MemoryCenter *oMemoryCenter, int img_w, int img_h)
{
    mVisualCenter = oVisualCenter;

    oMatching = new Matching (mVisualCenter, oMemoryCenter);
    oCoherence = new Coherence (oMemoryCenter, img_w, img_h);
    oConfidence = new Confidence ();
}


// Destructor
Recognition::~Recognition ()
{
    if (oMatching != NULL)
        delete (oMatching);
    if (oCoherence != NULL)
        delete (oCoherence);
     if (oConfidence != NULL)
        delete (oConfidence);
}


// This function implements the object recognition process. 
// It tries to identify the landmark among any of the stored models using appearance and contextual information.
// It returns true if the recognition was positive, or false otherwise.
bool Recognition::recogniseObject(CvSeq* seq_scene_objects, int* matched_object)
{
#ifdef DEBUG_MODE
	cout << " init - RecogniseLandmark" << endl;
#endif
	bool bpositive;
	CvSeq* seq_candidate_matches;
        int *lmkPosition = mVisualCenter->getLandmarkPosition();
	CvSeq* seqLmkContext = mVisualCenter->getLandmarkContext();
								  
	bpositive = false;
	*matched_object = -1;
	
	if (oMatching->doMatching())
	{
		seq_candidate_matches = oMatching->getListCandidateMatches();
					
		oCoherence->checkSelfCoherence (mVisualCenter->getLandmarkV2()->getArea(), lmkPosition, seq_candidate_matches);
		
		oCoherence->getLandmarkContext (seqLmkContext, lmkPosition, seq_scene_objects);

		oCoherence->checkGlobalCoherence(seqLmkContext, seq_candidate_matches);
		
		if (oConfidence->findConfidentMatches(seq_candidate_matches))
		{
                    bpositive = true;
                    *matched_object = oConfidence->getIdentifiedObject();
		}
	}				
							
#ifdef DEBUG_MODE
	cout << " end - RecogniseLandmark" << endl;
#endif	
	return (bpositive);
}
	

bool Recognition::isModelGood ()
{
	return (oConfidence->isRecognitionSafe());
}
}
