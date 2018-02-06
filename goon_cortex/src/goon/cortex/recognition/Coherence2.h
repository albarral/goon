#ifndef __GOON_CORTEX_COHERENCE2_H
#define __GOON_CORTEX_COHERENCE2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <opencv2/core/core.hpp>
#include <log4cxx/logger.h>
#include "goon/cortex/data/memory_center.h"		

namespace goon
{
class Coherence2
{
private:
    static log4cxx::LoggerPtr logger;
    MemoryCenter *mMemoryCenter;
    int visual_area_noise;

public:
        Coherence2(MemoryCenter* oMemoryCenter, int im_w, int img_h);
        ~Coherence2();

    void checkSelfCoherence2 (int lmk_size, int* lmk_global_position, CvSeq* seq_candidate_matches);
    // This function checks the (size, position) coherence of a match and updates its confidence value.
    // It compares the (size, position) of the landmark with the last (size, position) of the candidate object.

    void getLandmarkContext (CvSeq* seq_lmk_context, int* lmk_global_position, CvSeq* seq_recent_objects);
    // This function obtains a landmark's context by computing its relative positions towards the last detected objects in the scene.

    void checkGlobalCoherence2 (CvSeq* seq_lmk_context, CvSeq* seq_candidate_matches);
    // This function checks the global coherence of the candidate matches and updates their Coherence2 value.
    // It compares the positions of each landmark's neighbours with those of its candidate objects.
    // The final Coherence2 is affected by the sum of the self and context evidences.

private:
    float compareContexts (CvSeq* seq_lmk_context, st_object* object);
    // This function compares the context of a landmark with that of a candidate object and returns the context evidence value.
    // Single evidences appear when a neighbour is present in both contexts in a similar relative position.

    void showContextList (CvSeq* seq_context);
    // This function shows the given context list (for debug purpose).
};
}

#endif
