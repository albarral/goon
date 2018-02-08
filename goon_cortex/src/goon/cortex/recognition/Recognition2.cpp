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

    // get model of the object
    oModeling.modelObject(oObject, oObjectModel);
    
    //LOG4CXX_DEBUG(logger, oObjectModel.toString());
    
    if (oVisualMemory.getListModels().empty())
    {
        LOG4CXX_WARN(logger, "Recognition2: no models in visual memory, skip recognition");
        return false;
    }

    // match object model against models in visual memory
    if (oMatching2.doMatching(oObjectModel, oVisualMemory.getListModels())) 
    {
        oMatching2.showCandidates();
        
        //std::vector<st_match>& listCandidateMatches = oMatching2.getListCandidateMatches();

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
