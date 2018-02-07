#ifndef __GOON_CORTEX_MATCHING_H
#define __GOON_CORTEX_MATCHING_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <opencv2/core/core.hpp>
#include <log4cxx/logger.h>
#include "goon/cortex/recognition/matches.h"			
#include "goon/cortex/data/visual_center.h"
#include "goon/cortex/data/memory_center.h"
#include "utils/hsv_color.h"

namespace goon
{
class Matching
{
private:
        static log4cxx::LoggerPtr logger;
        VisualCenter* mVisualCenter;
        Landmark* oLandmark;
        MemoryCenter* mMemoryCenter;
        HSVColor *oHSVColor;
	float max_dist_color;
	bool bmark_regions;
	CvMat* mat_similarity;
	CvSeq* seq_correspondences;
	CvSeq* seq_matches;
	CvSeq* seq_candidate_matches;
        CvMemStorage* storage;

public:
        Matching(VisualCenter* oVisualCenter, MemoryCenter* oMemoryCenter);
        ~Matching();

        bool doMatching ();
	// This function performs a matching process between the landmark & the database models.
	// It returns true if there are matching candidates, otherwise it returns false.

        CvSeq* getListCandidateMatches ();
	// This function returns a pointer to the sequence of candidate matches.

private:
	bool compareLandmark2Model (st_model* model, st_match* match);
	// This function compares a landmark with a model in a region-region basis. It returns true if they are matched, or false otherwise.
	// The matching result is returned through the match structure.

	void checkLocalCoherence (st_lmk_region* lmk_region, st_model_region* model_region, st_anchor_match* anchor_match);
	// This function checks the local coherence of two matched regions through an exhaustive comparison of their corresponding neighbours.
	// It returns a matrix with all the obtained similarities to be used for finding region correspondences.

	bool compareRegions (st_lmk_region* lmk_region, st_model_region* model_region, st_anchor_match* anchor_match);
	// This function compares two regions based on weight, color and shape.  It returns true if the regions are similar, otherwise returns false.
	// Filter: 			weight, orientation
	// Similarity: 		color, shape

	bool compareNeighbours (st_neighbour* lmk_neighbour, st_neighbour* model_neighbour, float anchor_rotation, float* similarities);
	// This function compares a pair of neighbours based on position, color and scale. It returns true if the neighbours are similar, otherwise returns false.
	// Filter: 			module, angle, scale
	// Similarity: 		color, shape

	void findCorrespondences ();
	// This function establishes region correspondences between two landmarks through a nearest neighbours process (using their similarities)

	void filterCorrespondences (st_model* model);
	// This function eliminates nested correspondences.
	// If a collection is matched together with its subregions, all the correspondences involving these subregions have to be ignored.

	bool findRegionInList (CvSeq* seq_avoid_regions, int search_id);
	// This function searches for a specif region ID in a given list. It returns true if found or false otherwise.
	// When found, the item is removed from the list.

	void computeMatchedWeights (st_model* model, float* plmk_matched_weight, float* pmod_matched_weight);
	// This function computes the matched weights of a landmark and a model from their correspondences

	void unmarkLandmarkRegions ();
	// This function unmarks all landmark regions (for debugging purpose)

	void markLandmarkRegions (CvSeq* seq_aux);
	// This function marks matched landmark regions (for debugging purpose)

	void getBestCandidates ();
	// This function finds among all matched models the winner views of the best candidate objects, and puts them in seq_candidate_matches.
};
}
#endif
