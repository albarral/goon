#ifndef __GOON_CORTEX_RECOGNITION2_H
#define __GOON_CORTEX_RECOGNITION2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/cortex/recognition/Matching2.h"
#include "goon/cortex/recognition/Coherence2.h"
#include "goon/cortex/recognition/Confidence2.h"
#include "goon/data/VisualMemory.h"
#include "goon/data/cortex/Object.h"

namespace goon
{
class Recognition2
{
private:
    static log4cxx::LoggerPtr logger;
    Matching2 oMatching2;
    Coherence2 oCoherence2;
    Confidence2 oConfidence2;
  
public:
    Recognition2();
    //~Recognition2();

    // It implements the object recognition process.
    // It tries to identify the given object against the models in the given visual memory, using appearance, structural and contextual information.
    // It returns true if the recognition was positive, or false otherwise.
    bool recogniseObject(Object& oObject, VisualMemory& oVisualMemory);

    bool isModelGood ();
    // This function checks the validity of the identified model.
    // If the landmark was matched partially or matched with low similarity, the model is not safe and should be updated.
};
}
#endif
