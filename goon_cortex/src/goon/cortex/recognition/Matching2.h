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
#include "goon/features/color/HSVEssence.h"

namespace goon
{
class Matching2
{
private:
    static log4cxx::LoggerPtr logger;
    HSVEssence oHSVEssence;
    float max_dist_color;
    bool bmark_regions;
    cv::Mat mat_similarity;
    std::vector<st_match> seq_candidate_matches;
    
public:
    Matching2();
    //~Matching2();

    // this performs a matching process between the given object and the given list of object models.
    // It returns true if there are matching candidates, otherwise false.
    bool doMatching(Object& oObject, std::vector<ObjectModel>& listObjectModels);

    CvSeq* getListCandidateMatches ();
    // This function returns a pointer to the sequence of candidate matches.

private:
    // this compares an object with a model in a region-region basis. It returns true if they are matched, or false otherwise.
    // The matching result is returned through the match structure.
    bool compareObject2Model(Object& oObject, ObjectModel& oObjectModel, st_match& match);

    // compares two regions (body and model) based on weight, color and shape. It returns true if the regions are similar, otherwise returns false.
    bool compareRegions(Body& oBody, Model& oModel, st_anchor_match& anchor_match);
    
    // checks the local coherence of two matched regions through an exhaustive comparison of their corresponding neighbours.
    // It returns a matrix with all the obtained similarities to be used for finding region correspondences.
    void checkLocalCoherence(Body& oBody, Model& oModel, st_anchor_match& anchor_match);

    bool compareNeighbours (st_neighbour* lmk_neighbour, st_neighbour* model_neighbour, float anchor_rotation, float* similarities);
    // This function compares a pair of neighbours based on position, color and scale. It returns true if the neighbours are similar, otherwise returns false.
    // Filter: 			module, angle, scale
    // Similarity: 		color, shape

    // establish region correspondences between two landmarks through a nearest neighbours process (using their similarities)
    void findCorrespondences(std::vector<cv::Vec2i>& seq_correspondences);

    bool findRegionInList (CvSeq* seq_avoid_regions, int search_id);
    // This function searches for a specif region ID in a given list. It returns true if found or false otherwise.
    // When found, the item is removed from the list.

    void computeMatchedWeights (st_model* model, float* plmk_matched_weight, float* pmod_matched_weight);
    // This function computes the matched weights of a landmark and a model from their correspondences

    void unmarkLandmarkRegions ();
    // This function unmarks all landmark regions (for debugging purpose)

    void markLandmarkRegions (CvSeq* seq_aux);
    // This function marks matched landmark regions (for debugging purpose)

    // selects best candidate matches from the given list
    void getBestCandidates(std::vector<st_match>& seq_matches);
};
}
#endif
