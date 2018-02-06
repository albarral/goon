/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
		
#include <stdio.h>
		
#include "goon/cortex/recognition/coherence.h"	
#include "goon/cortex/recognition/matches.h"	
#include "goon/cortex/config/recognition_defines.h"

using namespace log4cxx;
namespace goon
{
LoggerPtr Coherence2::logger(Logger::getLogger("goon.cortex.recognition.coherence"));	  

// Constructor
Coherence2::Coherence2 (MemoryCenter* oMemoryCenter, int im_w, int im_h)
{
    mMemoryCenter = oMemoryCenter;
    visual_area_noise = im_w * im_h * VISUAL_AREA_NOISE / 100.0;

    LOG4CXX_INFO(logger, "parameters (SELF COHERENCE): visual noise = " << visual_area_noise);
    LOG4CXX_INFO(logger, "shown info -> self evidence (size evidence, pos evidence) size_factor, pos_dif");
    LOG4CXX_INFO(logger, "parameters (GLOBAL COHERENCE): position_tolerance = " << POSITION_TOLERANCE);
    LOG4CXX_INFO(logger, "shown info -> comparisons, total evidence\n");
}

// Destructor
Coherence2::~Coherence2 ()
{
}

// This function checks the (size, position) coherence of a match and updates its confidence value.
// It compares the (size, position) of the landmark with the last (size, position) of the candidate object.
void Coherence2::checkSelfCoherence2 (int lmk_size, int* lmk_global_position, CvSeq* seq_candidate_matches)
{
#ifdef DEBUG_MODE
	cout << " init - CheckSelfCoherence2" << endl;
#endif
	st_match *match;
	st_object* object;
	float size_evidence, pos_evidence;
	int object_size;
	float size_factor, pos_dif, xdif, ydif;

        LOG4CXX_DEBUG(logger, "Self ... ");

	// for each candidate match, compute its self evidence
	for (int i=0; i < seq_candidate_matches->total; i++)
	{
		match = (st_match*)cvGetSeqElem (seq_candidate_matches, i);
                object = mMemoryCenter->getObject(match->matched_object);

		object_size = object->last_size;

		if (lmk_size > object_size)
			size_factor = (float)(lmk_size - visual_area_noise) / object_size;
		else
			size_factor = (float)object_size / (lmk_size + visual_area_noise);

		// correct the influence of visual noise when it's comparable to size difference
		if (size_factor < 1.0)
			size_factor = 1.0;

		// negative size evidence when size factor higher than 1.0+SIZE_TOLERANCE
		size_evidence = 1.0 - ((size_factor - 1.0) / SIZE_TOLERANCE);

		xdif = lmk_global_position[0] - object->last_position[0];
		ydif = lmk_global_position[1] - object->last_position[1];
		pos_dif = sqrt(xdif*xdif + ydif*ydif);

		// negative position evidence when pos change is higher than MIN_POSITION_TOLERANCE
		pos_evidence = 1.0 - (pos_dif / MIN_POSITION_TOLERANCE);

		// self evidence is the worst of both
		match->self_evidence = MIN (size_evidence, pos_evidence);

		// limit self evidence
		match->self_evidence = MIN (1.0, match->self_evidence);
		match->self_evidence = MAX (-1.0, match->self_evidence);

                LOG4CXX_DEBUG(logger, "vs. object " << object->ID << ": size = " << (float)lmk_size/object_size << ", pos = " << pos_dif << "(" << size_evidence << " - " << pos_evidence << ") " << match->self_evidence);
	}

#ifdef DEBUG_MODE
	cout << " end - CheckSelfCoherence2" << endl;
#endif
}




// This function obtains a landmark's context by computing its relative positions towards the last detected objects in the scene.
void Coherence2::getLandmarkContext (CvSeq* seq_lmk_context, int* lmk_global_position, CvSeq* seq_recent_objects)
{
#ifdef DEBUG_MODE
	cout << " init - GetLandmarkContext" << endl;
#endif
	st_context context;
	int recent_object;
	st_object* object;
	int xdif, ydif;
	     		
	cvClearSeq (seq_lmk_context);
	
	// begin with most recent object
	for (int i=seq_recent_objects->total; i>0; i--)
	{
		recent_object = *(int*)cvGetSeqElem (seq_recent_objects, i);		
		
                object = mMemoryCenter->getObject(recent_object);

		xdif = object->last_position[0] - lmk_global_position[0];
		ydif = object->last_position[1] - lmk_global_position[1];
		
		context.object_ID = object->ID;
		context.rel_position[0] = xdif;
		context.rel_position[1] = ydif;
		context.module = sqrt(xdif*xdif + ydif*ydif);
		
		cvSeqPush (seq_lmk_context, &context);
	}	
			  
#ifdef DEBUG_MODE
	cout << " end - GetLandmarkContext" << endl;
#endif  
}



// This function checks the global coherence of the candidate matches and updates their confidence value. 
// It compares the positions of each landmark's neighbours with those of its candidate objects. 
// The final confidence is affected by the sum of the self and context evidences.
void Coherence2::checkGlobalCoherence2 (CvSeq* seq_lmk_context, CvSeq* seq_candidate_matches)
{
#ifdef DEBUG_MODE
	cout << " init - CheckGlobalCoherence2" << endl;
#endif
	st_match *match;
	st_object* object;
	float combined_evidence;
	
        LOG4CXX_DEBUG(logger, "Context ... ");
	  
	// for each candidate match, compute its context evidence
	for (int i=0; i < seq_candidate_matches->total; i++)
	{
		match = (st_match*)cvGetSeqElem (seq_candidate_matches, i);	
		
                object = mMemoryCenter->getObject(match->matched_object);
			
		// CompareContexts () 
		match->context_evidence = compareContexts (seq_lmk_context, object);
								
		combined_evidence = match->self_evidence + match->context_evidence;
		
		// update match confidence with evidence values
		match->confidence = match->quality * (1 + combined_evidence);
		// match->confidence = match->confidence * (1 + match->context_evidence);
		
		if (match->confidence < 0)
			match->confidence = 0;
	}
	  
#ifdef DEBUG_MODE
	cout << " end - CheckGlobalCoherence2" << endl;
#endif  
}


// This function compares the context of a landmark with that of a candidate object and returns the context evidence value. 
// Single evidences appear when a neighbour is present in both contexts in a similar relative position.
float Coherence2::compareContexts (CvSeq* seq_lmk_context, st_object* object)
{
#ifdef DEBUG_MODE
	cout << " init - CompareContexts" << endl;
#endif
	st_context *context1, *context2; 
	float evidence, single_evidence, pos_dif, pos_tolerance;
	int xdif, ydif;
	     	
	if (seq_lmk_context->total == 0 || object->seq_context->total == 0)
		return 0;

	evidence = 0;
	
	for (int i=0; i < object->seq_context->total; i++)
	{
            context1 = (st_context*)cvGetSeqElem (object->seq_context, i);

            // set the position tolerance for this context (with a lower limit)
            pos_tolerance = context1->module * POSITION_TOLERANCE;
            pos_tolerance = MAX (pos_tolerance, MIN_POSITION_TOLERANCE);

            for (int j=0; j < seq_lmk_context->total; j++)
            {
                context2 = (st_context*)cvGetSeqElem (seq_lmk_context, j);

                // if both context objects are the same, compare them
                if (context1->object_ID == context2->object_ID)
                {
                    xdif = context2->rel_position[0] - context1->rel_position[0];
                    ydif = context2->rel_position[1] - context1->rel_position[1];
                    pos_dif = (float)sqrt(xdif*xdif + ydif*ydif);

                    // negative evidence when pos change is higher than tolerance
                    single_evidence = 1.0 - (pos_dif / pos_tolerance);

                    LOG4CXX_DEBUG(logger, " -> object " << object->ID << " - context " << context1->object_ID << " (xdif=" << xdif << ", ydif=" << ydif << ", tolerance=" << pos_tolerance << ") " << single_evidence);

                    // limit context evidence
                    single_evidence = MIN (1.0, single_evidence);
                    single_evidence = MAX (-1.0, single_evidence);

                    evidence += single_evidence;
                    break;	// once compared exit this for and check next context1
                }
            }
	}

        LOG4CXX_DEBUG(logger, "	-> total_evidence = " << evidence);
			  
#ifdef DEBUG_MODE
	cout << " end - CompareContexts" << endl;
#endif

  return (evidence);
}



// This function shows the given context list (for debug purpose).
void Coherence2::showContextList (CvSeq* seq_context)
{
#ifdef DEBUG_MODE
	cout << " init - ShowContextList" << endl;
#endif
	st_context *context;
	     	
	for (int i=0; i < seq_context->total; i++)
	{
            context = (st_context*)cvGetSeqElem (seq_context, i);
            LOG4CXX_DEBUG(logger, " -> context " << context->object_ID << "(x,y) = (" << context->rel_position[0] << ", " << context->rel_position[1] << ") module=" << context->module);
	}
	  
#ifdef DEBUG_MODE
	cout << " end - ShowContextList" << endl;
#endif  
}
}


	
