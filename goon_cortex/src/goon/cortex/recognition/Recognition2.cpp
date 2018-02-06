/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "goon/cortex/recognition/Recognition2.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr Recognition2::logger(Logger::getLogger("goon.cortex.recognition"));

Recognition2::Recognition2()
{
}

//Recognition2::~Recognition2 ()
//{
//}


bool Recognition2::recogniseObject(Object& oObject, VisualMemory& oVisualMemory)
{
    LOG4CXX_TRACE(logger, "Recognition2.recogniseObject");

//    CvSeq* seq_candidate_matches;
//    int *lmkPosition = mVisualCenter->getLandmarkPosition();
//    CvSeq* seqLmkContext = mVisualCenter->getLandmarkContext();

    if (oMatching2.doMatching(oObject, oVisualMemory.getListModels())) 
    {
//        seq_candidate_matches = oMatching->getListCandidateMatches();
//
//        oCoherence2->checkSelfCoherence(mVisualCenter->getLandmarkV2()->getArea(), lmkPosition, seq_candidate_matches);
//
//        oCoherence2->getLandmarkContext(seqLmkContext, lmkPosition, seq_scene_objects);
//
//        oCoherence2->checkGlobalCoherence(seqLmkContext, seq_candidate_matches);
//
//        bool bpositive = oConfidence2->findConfidentMatches(seq_candidate_matches);

        //*matched_object = oConfidence2->getIdentifiedObject();
        return true;
    }		
    else 
        return false;
}
	

bool Recognition2::isModelGood ()
{
//    return (oConfidence2.isRecognitionSafe());
    return false;
}
}
