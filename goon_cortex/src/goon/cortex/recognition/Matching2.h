#ifndef __GOON_CORTEX_MATCHING2_H
#define __GOON_CORTEX_MATCHING2_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <vector>
#include <log4cxx/logger.h>

#include <opencv2/core/core.hpp>

#include "goon/cortex/recognition/matches.h"			
#include "goon/data/cortex/Model.h"
#include "goon/data/cortex/Object.h"
#include "goon/data/cortex/ObjectModel.h"
#include "goon/features/Body.h"
#include "goon/features/color/HSVEssence.h"

namespace goon
{
class Matching2
{
public:
    typedef cv::Vec<float, 5> Vec5f;    // for similarity vectors

    enum eSimilarity
    {
        eSIM_COLOR,
        eSIM_SHAPE,
        eSIM_WEIGHT,
        eSIM_ANGLE,
        eSIM_TOTAL,
        eSIM_DIM
    };
private:
    static log4cxx::LoggerPtr logger;
    // params
    float max_dist_color;
    float maxRotation;
    float reqSimilarity;
    float reqQuality;       // minimum required quality to consider a feasible matching
    // logic
    HSVEssence oHSVEssence;
    cv::Mat mat_similarity;     // eSIM_DIM depth
    std::vector<cv::Vec2i> seq_correspondences;     // region correspondences
    std::vector<st_match> seq_candidate_matches;    
    
public:
    Matching2();
    //~Matching2();

    // Performs a matching process between the given object and the given list of object models.
    // It returns true if there are matching candidates, false otherwise
    bool doMatching(Object& oObject, std::vector<ObjectModel>& listObjectModels);

    // get access to the sequence of candidate matches.
    std::vector<st_match>& getListCandidateMatches() {return seq_candidate_matches;};

private:
    // compare an object with a model in a region-region basis
    // it returns the matching quality and informs the given match data
    float compareObject2Model(Object& oObject, ObjectModel& oObjectModel, st_match& match);

    // compares two regions (body and model) based on color, shape, weight and orientation. It returns a vector with those four similarities.
    Vec5f compareRegions(Body& oBody, Model& oModel);
    
    // establish region correspondences between object regions and model regions (using the similarity matrix)
    void findCorrespondences();
    
    // computes a quality measure for the object-model comparison
    float computeMatchingQuality(Object& oObject, ObjectModel& oObjectModel);

    // computes the matched fractions of the object and the model
    cv::Vec2f computeMatchedFractions(Object& oObject, ObjectModel& oObjectModel);

    // selects best candidate matches from the given list
    //void filterCandidates();
};
}
#endif
