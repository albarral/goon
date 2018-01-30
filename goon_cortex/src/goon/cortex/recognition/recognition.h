#ifndef __GOON_CORTEX_RECOGNITION_H
#define __GOON_CORTEX_RECOGNITION_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/core/core.hpp>

#include "goon/cortex/data/visual_center.h"
#include "goon/cortex/data/memory_center.h"
#include "goon/data/VisualMemory.h"
#include "goon/cortex/recognition/matching.h"
#include "goon/cortex/recognition/coherence.h"
#include "goon/cortex/recognition/confidence.h"

namespace goon
{
class Recognition
{
    private:
        VisualCenter* mVisualCenter;
        Matching* oMatching;
        Coherence* oCoherence;
        Confidence* oConfidence;

    public:
        Recognition (VisualCenter* oVisualCenter, MemoryCenter *oMemoryCenter, int img_w, int img_h);
        ~Recognition();

        bool recogniseObject (CvSeq* seq_scene_objects, int *matched_object);
        // This function implements the object recognition process.
        // It tries to identify the landmark among any of the stored models using appearance and contextual information.
        // It returns true if the recognition was positive, or false otherwise.

        bool isModelGood ();
	// This function checks the validity of the identified model.
	// If the landmark was matched partially or matched with low similarity, the model is not safe and should be updated.

};
}
#endif
