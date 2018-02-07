/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
		
#include <stdio.h>
		
#include "goon/cortex/recognition/matching.h"
#include "goon/cortex/config/recognition_defines.h"
#include "utils/hsv_color.h"
#include "goon/features/shape/shape.h"
#include "goon/cortex/config/vision_defines.h"
							
using namespace log4cxx;

namespace goon
{
LoggerPtr Matching::logger(Logger::getLogger("goon.cortex.recognition.matching"));

// data structure to store best candidates info
typedef struct st_candidate
{
	int object;
	float quality;
	int match_position;
}
st_candidate;


// Constructor
Matching::Matching (VisualCenter* oVisualCenter, MemoryCenter* oMemoryCenter)
{
    mVisualCenter = oVisualCenter;
    mMemoryCenter = oMemoryCenter;
    oHSVColor = new HSVColor();

    storage = cvCreateMemStorage(0);

    seq_correspondences = cvCreateSeq( CV_32SC2, sizeof(CvSeq),2*sizeof(int), storage);
    seq_matches = cvCreateSeq( CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_match), storage);
    seq_candidate_matches = cvCreateSeq( CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_match), storage);

    // set maximum color distance (red-yellow)
    float hsvRed[3] = {0, 255, 255};
    float hsvYellow[3] = {60, 255, 255};
    // HSVColorDistance ()
    max_dist_color = oHSVColor->getDistance (hsvRed, hsvYellow, HSVColor::eSAME_COLOR);

    LOG4CXX_INFO(logger, "MATCHING parameters -> (match quality, local tolerance, similarity) = (" << MATCH_QUALITY << ", " << LOCAL_TOLERANCE << ", " << SIMILARITY << ")");
    LOG4CXX_INFO(logger, "shown info -> matched regions (lmk weight, model weight, color similarity, shape similarity) quality");
}


Matching::~Matching ()
{
    cvReleaseMemStorage (&storage );

    if (oHSVColor != NULL)
        delete (oHSVColor);
}


// This function performs a matching process between the specified landmark & the database models 
// It returns true if there are matching candidates, otherwise it returns false.		
bool Matching::doMatching ()
{
#ifdef DEBUG_MODE
	cout << " init - DoMatching" << endl;
#endif        
	st_model* model;	
	st_match match;
	float scale_factor, lmkScale;
	bool bmatched = false;
        int numModels = mMemoryCenter->getNumModels();
					
	cvClearSeq (seq_matches);
	cvClearSeq (seq_candidate_matches);
	bmark_regions = false;

        oLandmark = mVisualCenter->getLandmarkV2(); // done everytime because of Lmk cloning
        lmkScale = oLandmark->getScale();
	
  	// for each model
	for (int j=1; j<=numModels; j++)
	{								
            model = mMemoryCenter->getModel(j);

            // compare landmark vs model only if they are coherent in scale
            scale_factor = MAX (lmkScale, model->scale) / MIN(lmkScale, model->scale);

            if (scale_factor < MAX_SCALE_FACTOR)
            {
                bmatched = compareLandmark2Model (model, &match);

                // if matched, the model is added to the list of candidate matches for this landmark
                if (bmatched)
                {
                        match.modelID = model->object_ID;
                        match.matched_view = model->view_ID;
                        cvSeqPush (seq_matches, &match);
                }
            }
	} 
	  		  	  	  				
	// if single candidate, add as best candidate
	if (seq_matches->total == 1)
	{
		cvSeqPop (seq_matches, &match);				
		cvSeqPush (seq_candidate_matches, &match);
	}
	// if many candidates -> find the best matched view from each object
	else if (seq_matches->total > 1)
	{
            getBestCandidates ();

            LOG4CXX_DEBUG(logger, "           best_candidates = " << seq_candidate_matches->total);
	}		
		     		  
#ifdef DEBUG_MODE
	cout << " end - DoMatching" << endl;
#endif  
	return (seq_candidate_matches->total > 0);
}



// This function compares a landmark with a model in a region-region basis. It returns true if they are matched, or false otherwise.
// The matching result is returned through the match structure.
bool Matching::compareLandmark2Model (st_model* model, st_match* match)
{
#ifdef DEBUG_MODE
	cout << " init - CompareLandmarkModel2" << endl;
#endif
	bool bmatched;
	st_lmk_region* lmk_region;
	st_model_region* model_region;
	CvSeq* seq_aux;
	int num_regions, region2;
	bool banchored;
	st_anchor_match anchor_match;
	st_anchor_match best_anchor_match;
	float match_quality;
	int matched_regions;
	float lmk_matched_weight, mod_matched_weight, min_matched_weight;
	float best_quality;
	int best_matched_regions;
	float best_lmk_weight, best_mod_weight;
						  		  				 				
	mat_similarity = cvCreateMat (oLandmark->getNumRegions(), model->num_regions, CV_32FC1);
	cvClearSeq (seq_correspondences);													

	bmatched = false;	
	best_quality = -100.0;
	best_matched_regions = 0;
	best_lmk_weight = best_mod_weight = 0.0;
	best_anchor_match.rotation = best_anchor_match.color_similarity = best_anchor_match.shape_similarity = 0.0;

        num_regions = oLandmark->getNumRegions();
	// compare landmark regions vs. model regions (until a basic region is anchored)
	for (int k=0; k < num_regions; k++)
	{
            // exit condition (landmark matched)
            if (bmatched)
                    break;

            lmk_region = oLandmark->getRegion(k);

            for (int l=0; l < model->num_regions; l++)
            {
                // exit condition (landmark matched)
                if (bmatched)
                        break;

                region2 = model->list_regions[l];
                model_region = mMemoryCenter->getModelRegion(region2);

                banchored = compareRegions (lmk_region, model_region, &anchor_match);

                // if basic regions are similar -> anchor them and check local coherence
                if (banchored)
                {
                    cvZero (mat_similarity);

                    // CheckLocalCoherence()
                    checkLocalCoherence (lmk_region, model_region, &anchor_match);

                    // Establish region correspondences following a nearest neighbour strategy
                    // FindCorrespondences()
                    findCorrespondences ();

                    // FilterCorrespondences ()
                    filterCorrespondences (model);

                    if (bmark_regions)
                            seq_aux = cvCloneSeq (seq_correspondences, storage);

                    // compute matched weights
                    matched_regions = 1 + seq_correspondences->total;
                    lmk_matched_weight = lmk_region->weight;
                    mod_matched_weight = model_region->weight;

                    // ComputeMatchedWeights()
                    computeMatchedWeights (model, &lmk_matched_weight, &mod_matched_weight);

                    // COMPUTE MATCH QUALITY (use the smaller of the matched weights)

                    min_matched_weight = MIN (lmk_matched_weight, mod_matched_weight);
                    match_quality = matched_regions * min_matched_weight;			// linear version
                    //match_quality = 1.0 - exp (-1 * matched_regions * min_matched_weight / (100 - min_matched_weight));			// exponential version
                    //match_quality = (matched_regions*lmk_matched_weight - (100 - lmk_matched_weight)) * mod_matched_weight / 100;			// Q10
                    //match_quality = matched_regions * lmk_matched_weight * mod_matched_weight / 100;		// Q4

                    // if best matching till now -> check if landmark matched
                    if (match_quality > best_quality)
                    {
                            best_quality = match_quality;
                            best_matched_regions = matched_regions;
                            best_lmk_weight = lmk_matched_weight;
                            best_mod_weight = mod_matched_weight;

                            best_anchor_match.rotation = anchor_match.rotation;
                            best_anchor_match.color_similarity = anchor_match.color_similarity;
                            best_anchor_match.shape_similarity = anchor_match.shape_similarity;

                            if (bmark_regions)
                            {
                                    // UnmarkLandmarkRegions()
                                    unmarkLandmarkRegions ();
                                    // MarkLandmarkRegions()
                                    markLandmarkRegions(seq_aux);
                                    lmk_region->matched = 1;
                            }

                            // MATCHING CONDITION
                            if (match_quality > MATCH_QUALITY)
                                    bmatched = true;
                    }

                    if (bmark_regions)
                            cvClearSeq (seq_aux);
                }
            }
	}
		  			  		  
	cvReleaseMat (&mat_similarity);

	if (best_matched_regions > 0)
        {
            LOG4CXX_DEBUG(logger, " vs. model " << model->object_ID << "." << model->view_ID << " = " << best_matched_regions << " cors - q = " << best_quality);
            LOG4CXX_DEBUG(logger, "                 (lmk weight, model weight, color sim, shape sim) = " << (int)best_lmk_weight << "%, " << (int)best_mod_weight << "%, " << best_anchor_match.color_similarity << ", " <<  best_anchor_match.shape_similarity << ")");
        }
	
	match->quality = best_quality;
	match->objectMatchedFraction = best_lmk_weight;
	match->modelMatchedFraction = best_mod_weight;
	match->lowest_similarity = MIN (best_anchor_match.color_similarity, best_anchor_match.shape_similarity);
	
#ifdef DEBUG_MODE
	cout << " end - CompareLandmarkModel2" << endl;
#endif  
	return(bmatched);
} 




// This function checks the local coherence of two matched regions through an exhaustive comparison of their corresponding neighbours.
// It returns a matrix with all the obtained similarities to be used for finding region correspondences.
void Matching::checkLocalCoherence (st_lmk_region* lmk_region, st_model_region* model_region, st_anchor_match* anchor_match)
{
#ifdef DEBUG_MODE
	cout << " init - CheckLocalCoherence" << endl;
#endif
	float *pmat_similarity;
	int reg1, reg2;
	float similarities[2]; //  {color, shape}
	bool neighbours_matched;
		
	if (lmk_region->num_neighbours == 0 || model_region->num_neighbours == 0)
		return;
				
	// compare all the neighbours in the landmark vs. all the neighbours in the model 
	for (int k=0; k < lmk_region->num_neighbours; k++)
	{
		reg1 = lmk_region->neighbours[k].ID;
		
		for (int l=0; l < model_region->num_neighbours; l++)
		{										
			reg2 = model_region->neighbours[l].ID;
			pmat_similarity = (float*)cvPtr2D (mat_similarity, reg1, reg2);				  
									
			// CompareNeighbours()
			neighbours_matched = compareNeighbours (&lmk_region->neighbours[k], &model_region->neighbours[l], anchor_match->rotation, similarities);
			
			// if  matched, compute overall similarity 
			if (neighbours_matched)
				//*pmat_similarity = (similarities[0] + similarities[1])/2;				
				*pmat_similarity = similarities[0];				
			else 
				*pmat_similarity = 0.0;				
		} 
	}
	
#ifdef DEBUG_MODE
	cout << " end - CheckLocalCoherence" << endl;
#endif  
} 



// This function compares two regions based on color and shape.  It returns true if the regions are similar, otherwise returns false.
// Filter: 			orientation
// Similarity: 		color, shape
bool Matching::compareRegions (st_lmk_region* lmk_region, st_model_region* model_region, st_anchor_match* anchor_match)
{
#ifdef DEBUG_MODE
	cout << " init - CompareRegions" << endl;	
#endif
	bool similar = false;
	float anchor_rotation;
	float dist_color, color_similarity, shape_similarity;
  			
	// get orientation difference
	if (lmk_region->orientation != Shape::UNDEFINED_ORIENTATION && model_region->orientation != Shape::UNDEFINED_ORIENTATION)
	{
		anchor_rotation = lmk_region->orientation - model_region->orientation;
		anchor_rotation = CYCLIC_DIF (anchor_rotation, 180); // region's orientation is in range [-90, 90]
	}
	else 
		anchor_rotation = 0;

	// FILTER: orientation
	if (fabs(anchor_rotation) < MAX_LMK_ROTATION)
	{	
		// HSVColorDistance()
		dist_color = oHSVColor->getDistance (lmk_region->color, model_region->color, HSVColor::eSAME_COLOR);
		color_similarity = 1.0 - (dist_color/max_dist_color);
					 
		shape_similarity = MIN (lmk_region->shape_factor, model_region->shape_factor) / MAX (lmk_region->shape_factor, model_region->shape_factor);		
		
		// SIMILARITY: color & shape	 
		if  ( color_similarity > SIMILARITY && shape_similarity > SIMILARITY)			
			similar = true;
	}
	
	anchor_match->rotation = anchor_rotation;
	anchor_match->color_similarity = color_similarity;
	anchor_match->shape_similarity = shape_similarity;
	return (similar);
				  
#ifdef DEBUG_MODE
	cout << " end - CompareRegions" << endl;
#endif
} 



// This function compares a pair of neighbours based on position, color and scale. It returns true if the neighbours are similar, otherwise returns false.
// Filter: 			module, angle, scale
// Similarity: 		color
bool Matching::compareNeighbours (st_neighbour* lmk_neighbour, st_neighbour* model_neighbour, float anchor_rotation, float* similarities)
{
#ifdef DEBUG_MODE
	cout << " init - CompareNeighbours" << endl;	
#endif
	bool similar = false;
	float module_dif, angle_dif;
	float dist_color, color_similarity = 0.0, shape_similarity = 0.0;  
	float scale_factor;
	
	module_dif = fabs(lmk_neighbour->rel_position[0] - model_neighbour->rel_position[0]) / (MAX (lmk_neighbour->rel_position[0], model_neighbour->rel_position[0]));
	
	// relative angle difference (considering anchor rotation)
	angle_dif = lmk_neighbour->rel_position[1] - model_neighbour->rel_position[1] - anchor_rotation;
	angle_dif = CYCLIC_DIF (angle_dif, 360); // neighbour's angle is in range [-180, 180]
		
	// compare the relative scales using the major/minor scale factor
	if (lmk_neighbour->rel_weight > model_neighbour->rel_weight)
		scale_factor = lmk_neighbour->rel_weight / (model_neighbour->rel_weight * (1+SIZE_VARIABILITY));
	else
		scale_factor =  (model_neighbour->rel_weight * (1-SIZE_VARIABILITY)) / lmk_neighbour->rel_weight;
	
	if (scale_factor < 1.0)
		scale_factor = 1.0;
		
	// FILTER: module & angle & scale
	if (module_dif < LOCAL_TOLERANCE && fabs(angle_dif) < 90*LOCAL_TOLERANCE && scale_factor < (1+LOCAL_TOLERANCE)) 
	{
		// HSVColorDistance()
		dist_color = oHSVColor->getDistance (lmk_neighbour->color, model_neighbour->color, HSVColor::eSAME_COLOR);
		color_similarity = 1.0 - (dist_color/max_dist_color);
					 
		//shape_similarity = MIN (lmk_neighbour->shape_factor, model_neighbour->shape_factor) / MAX (lmk_neighbour->shape_factor, model_neighbour->shape_factor);		
		
		// SIMILARITY: color & shape	 		
		//if  ( color_similarity > SIMILARITY && shape_similarity > SIMILARITY)			
		if  ( color_similarity > SIMILARITY)			
				similar = true;
	}
		
	similarities[0] = color_similarity;
	similarities[1] = shape_similarity;
	return (similar);
				  
#ifdef DEBUG_MODE
	cout << " end - CompareNeighbours" << endl;
#endif
} 



// This function establishes region correspondences between two landmarks through a nearest neighbours process (using their similarities)
void Matching::findCorrespondences ()
{	
#ifdef DEBUG_MODE
	cout << " init - FindCorrespondences" << endl;	
#endif
	int row, col;
	double max_similarity;
	CvPoint max_point;
	CvMat mat_row, mat_col;
	int correspondence[2];
	
	max_similarity = 1.0;
		  
	// Clear sequence of correspondences
	cvClearSeq (seq_correspondences);
		
	// establish correspondences between the most similar region-region pairs
	while (max_similarity > 0)
	{
		cvMinMaxLoc (mat_similarity, 0, &max_similarity,  0, &max_point);
		
		if (max_similarity > 0)
		{
			// increase sequence of matches
			row = max_point.y; 
			col = max_point.x;			
			correspondence[0] = row; // region position (in landmark)
			correspondence[1] = col; // region position (in model)
			cvSeqPush (seq_correspondences, &correspondence);
						
			// extract best region-region pair from the matrix
			cvGetRow (mat_similarity, &mat_row, row);
			cvZero(&mat_row);
			cvGetCol (mat_similarity, &mat_col, col);			
			cvZero(&mat_col);			
		}					
	}
	
#ifdef DEBUG_MODE
	cout << " end - FindCorrespondences" << endl;	
#endif
}
 
 
 
// This function eliminates nested correspondences. 
// If a collection is matched together with its subregions, all the correspondences involving these subregions have to be ignored.
void Matching::filterCorrespondences (st_model* model)
{
#ifdef DEBUG_MODE
	cout << " init - FilterCorrespondences" << endl;
#endif
	int* correspondence;
	int region2;
	CvSeq* seq_subregions;				
	int subregion1_id, subregion2_id;		
	int k;	
	bool binvalid_correspondence;
	CvSeq* seq_avoid_lmk_regions;				
	CvSeq* seq_avoid_mod_regions;
        st_lmk_region* lmk_region;
        st_model_region* model_region;
						
	if (seq_correspondences->total < 2)
		return;
	
	seq_avoid_lmk_regions = cvCreateSeq (CV_32SC1, sizeof(CvSeq),sizeof(int), storage);
	seq_avoid_mod_regions = cvCreateSeq (CV_32SC1, sizeof(CvSeq),sizeof(int), storage);
	
	// FIRST, search the correspondences for collections 
	
	// find all the collections in the correspondences (lmk or model) and list their subregions to be avoided
	for (int i=0; i < seq_correspondences->total; i++)
	{		  		
		correspondence = (int*)cvGetSeqElem (seq_correspondences, i);		
		
		// if the lmk region is a collection, add its subregions to an avoid list
                lmk_region = oLandmark->getRegion(correspondence[0]);
		if (lmk_region->seq_subregions->total > 0)
		{
			seq_subregions = lmk_region->seq_subregions;
			for (int j=0; j<seq_subregions->total; j++)
			{		  		
				subregion1_id = *(int*)cvGetSeqElem (seq_subregions, j);
				
				cvSeqPush (seq_avoid_lmk_regions, &subregion1_id);
			}			 
		}			
		
		// if the model region is a collection, add its subregions to an avoid list
		region2 = model->list_regions[correspondence[1]];
                model_region = mMemoryCenter->getModelRegion(region2);
		if (model_region->seq_subregions->total > 0)
		{
			seq_subregions = model_region->seq_subregions;
			for (int j=0; j<seq_subregions->total; j++)
			{		  		
				subregion2_id = *(int*)cvGetSeqElem(seq_subregions, j);
				
				cvSeqPush (seq_avoid_mod_regions, &subregion2_id);
			}			 
		}					
	}
									
	// if no regions to be avoided, finish the process and return
	if (seq_avoid_lmk_regions->total == 0 && seq_avoid_mod_regions->total == 0)
		return;
	
	// SECOND, search the correspondences for regions to be avoided
	
	k = 0;
	while (k < seq_correspondences->total)
	{		  		
		binvalid_correspondence = false;
		
		correspondence = (int*)cvGetSeqElem (seq_correspondences, k);		
		
                lmk_region = oLandmark->getRegion(correspondence[0]);
		if (lmk_region->seq_subregions->total == 0)
		{
			// FindRegionInList ()
			if (findRegionInList (seq_avoid_lmk_regions, lmk_region->ID))
				binvalid_correspondence = true;							
		}
			
		region2 = model->list_regions[correspondence[1]];
                model_region = mMemoryCenter->getModelRegion(region2);
		if (model_region->seq_subregions->total == 0)
		{
			// FindRegionInList ()
			if (findRegionInList (seq_avoid_mod_regions, model_region->ID))
				binvalid_correspondence = true;							
		}
		
		// if this correspondence involves a region to be avoided, remove correspondence
		if (binvalid_correspondence)
			cvSeqRemove (seq_correspondences, k);
		else
			k ++;
					
		// if no more regions to be avoided, finish the process
		if (seq_avoid_lmk_regions->total == 0 && seq_avoid_mod_regions->total == 0)
			break;
	}
			
	cvClearSeq (seq_avoid_lmk_regions);
	cvClearSeq (seq_avoid_mod_regions);

#ifdef DEBUG_MODE
	cout << " end  - FilterCorrespondences" << endl;
#endif
}
  


// This function searches for a specif region ID in a given list. It returns true if found or false otherwise. 
// When found, the item is removed from the list.
bool Matching::findRegionInList (CvSeq* seq_avoid_regions, int search_id)
{
#ifdef DEBUG_MODE
	cout << " init - FindRegionInList" << endl;
#endif
	bool bfound = false;					
	int* avoid_id;
	
	for (int i=0; i < seq_avoid_regions->total; i++)
	{	
		avoid_id = (int*)cvGetSeqElem (seq_avoid_regions, i);		

		if (*avoid_id == search_id)
		{
			bfound = true;
			cvSeqRemove (seq_avoid_regions, i);
			break;
		}
	}
	
	return (bfound);

#ifdef DEBUG_MODE
	cout << " end  - FindRegionInList" << endl;
#endif	
}


 
// This function computes the matched weights of a landmark and a model from their correspondences
void Matching::computeMatchedWeights (st_model* model, float* plmk_matched_weight, float* pmod_matched_weight)
{
	int region2;
	int correspondence[2];
		
	while (seq_correspondences->total > 0)
	{
		cvSeqPop (seq_correspondences, &correspondence);
		region2 = model->list_regions[correspondence[1]];

		*plmk_matched_weight += oLandmark->getRegion(correspondence[0])->weight;
		*pmod_matched_weight += mMemoryCenter->getModelRegion(region2)->weight;
	}
}


 
// This function unmarks all landmark regions (for debugging purpose)
void Matching::unmarkLandmarkRegions ()
{
    int num_regions = oLandmark->getNumRegions();

    // clear all marks
    for (int i=0; i < num_regions; i++)
    {
            oLandmark->getRegion(i)->matched = 0;
    }
}
				
 

// This function marks matched landmark regions (for debugging purpose)
void Matching::markLandmarkRegions (CvSeq* seq_aux)
{
	int correspondence[2];
		
	while (seq_aux->total > 0)
	{
		cvSeqPop (seq_aux, &correspondence);
		oLandmark->getRegion(correspondence[0])->matched = 2;
	}													
}



// This function finds among all matched models the winner views of the best candidate objects, and puts them in seq_candidate_matches.
void Matching::getBestCandidates ()
{	
#ifdef DEBUG_MODE
	cout << " init - GetBestCandidates" << endl;	
#endif
	CvSeq* seq_candidates = cvCreateSeq( CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_candidate), storage);
	st_candidate *candidate;
	st_candidate new_candidate;
	st_match *match;
	int matched_object;
	bool bcandidate_found;

	// FIND WINNER VIEWS OF BEST CANDIDATE OBJECTS
	
	// for each candidate match
	for (int i=0; i < seq_matches->total; i++)
	{
		match = (st_match*)cvGetSeqElem (seq_matches, i);		
		
		matched_object = match->modelID;
		
		// check if matched object is already a candidate
		bcandidate_found = false;
		for (int j=0; j < seq_candidates->total; j++)
		{
			candidate = (st_candidate*)cvGetSeqElem (seq_candidates, j);		
			
			if (matched_object == candidate->object)
			{
				bcandidate_found = true;
				break;
			}
		}
		
		// if matched object was a candidate
		if (bcandidate_found)
		{	
			// update it only if new view was better matched
			if (match->quality > candidate->quality)
			{
				candidate->quality = match->quality;
				candidate->match_position = i;
			}
		}
		// otherwise add it as new candidate
		else
		{
			new_candidate.object = matched_object;
			new_candidate.quality = match->quality;
			new_candidate.match_position = i;
			
			cvSeqPush (seq_candidates, &new_candidate);
		}		
	}	// end for
		
	// Put the winner views in seq_candidate_matches	
	for (int k=0; k < seq_candidates->total; k++)
	{
		candidate = (st_candidate*)cvGetSeqElem (seq_candidates, k);		

		match = (st_match*)cvGetSeqElem (seq_matches, candidate->match_position);		
				
		cvSeqPush (seq_candidate_matches, match); 	
	}	
		
	cvClearSeq (seq_candidates);
		
#ifdef DEBUG_MODE
	cout << " end - GetBestCandidates" << endl;	
#endif
}



// This function returns a pointer to the sequence of candidate matches.
CvSeq* Matching::getListCandidateMatches ()
{			
	return (seq_candidate_matches);
}  
}
