/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "goon/cortex/recognition/Matching2.h"
#include "goon/cortex/config/recognition_defines.h"
#include "goon/features/shape/shape.h"
#include "goon/cortex/config/vision_defines.h"
#include "maty/math/Angle.h"
							
using namespace log4cxx;

namespace goon
{
LoggerPtr Matching2::logger(Logger::getLogger("goon.cortex.recognition.matching"));

// data structure to store best candidates info
typedef struct st_candidate
{
	int object;
	float quality;
	int match_position;
}
st_candidate;


// Constructor
Matching2::Matching2()
{
    max_dist_color = 1.0;
    
    LOG4CXX_INFO(logger, "MATCHING parameters -> (match quality, local tolerance, similarity) = (" << MATCH_QUALITY << ", " << LOCAL_TOLERANCE << ", " << SIMILARITY << ")");
    LOG4CXX_INFO(logger, "shown info -> matched regions (lmk weight, model weight, color similarity, shape similarity) quality");
}

//Matching2::~Matching2 ()
//{
//}


// This function performs a matching process between the specified landmark & the database models 
// It returns true if there are matching candidates, otherwise it returns false.		
bool Matching2::doMatching(Object& oObject, std::vector<ObjectModel>& listObjectModels)
{
    LOG4CXX_TRACE(logger, "Matching2.doMatching");
    
    seq_candidate_matches.clear();
    std::vector<st_match> seq_matches;
    st_match match;					
    bmark_regions = false;
	
    // for each model
    for (ObjectModel& oObjectModel : listObjectModels)
    {		
        // compare object and model
        // if matched, add new match 
        if (compareObject2Model(oObject, oObjectModel, &match))
        {
            match.matched_object = oObjectModel.getID();
            seq_matches.push_back(match);
        }
    } 

    // if single candidate, add as best candidate
    if (seq_matches.size() == 1)            
        seq_candidate_matches.push_back(match);
    // if many candidates -> find the best 
    else if (!seq_matches.empty())
    {
        getBestCandidates(seq_matches);
        LOG4CXX_DEBUG(logger, "best_candidates = " << seq_candidate_matches.size());
    }		
		     		  
    return (!seq_candidate_matches.empty());
}


bool Matching2::compareObject2Model(Object& oObject, ObjectModel& oObjectModel, st_match& match)
{
    LOG4CXX_TRACE(logger, "Matching2.compareObject2Model");

    bool banchored;
    st_anchor_match anchor_match;
    st_anchor_match best_anchor_match;
    float match_quality;
    int matched_regions;
    float lmk_matched_weight, mod_matched_weight, min_matched_weight;

    // similarity matrix
    int rows = oObject.getSubBodies().size();
    int cols = oObjectModel.getSubModels().size();
    mat_similarity = cv::Mat::zeros(rows, cols, CV_32FC1);
    // correspondences list
    std::vector<cv::Vec2i> seq_correspondences;

    bool bmatched = false;	
    float best_quality = -100.0;
    int best_matched_regions = 0;
    float best_lmk_weight = 0.0, best_mod_weight = 0.0;
    best_anchor_match.rotation = best_anchor_match.color_similarity = best_anchor_match.shape_similarity = 0.0;

    // compare object subodies with object model submodels (until a pair is anchored)
    int k=0;
    for (Body& oBody : oObject.getSubBodies())
    {
        // exit condition (landmark matched)
        if (bmatched)
                break;

        int l = 0;
        for (Model& oModel : oObjectModel.getSubModels()) 
        {
            // exit condition (landmark matched)
            if (bmatched)
                break;

            banchored = compareRegions(oBody, oModel, anchor_match);

            // if basic regions are similar -> anchor them and check local coherence
            if (banchored) 
            {
                checkLocalCoherence(oBody, oModel, anchor_match);

                // establish region correspondences following a nearest neighbour strategy
                findCorrespondences(seq_correspondences);

                // compute matched weights
                matched_regions = 1 + seq_correspondences.size();
                lmk_matched_weight = oBody.getMass();
                mod_matched_weight = oModel.getMass();

                // ComputeMatchedWeights()
                computeMatchedWeights(model, &lmk_matched_weight, &mod_matched_weight);

                // COMPUTE MATCH QUALITY (use the smaller of the matched weights)

                min_matched_weight = MIN(lmk_matched_weight, mod_matched_weight);
                match_quality = matched_regions * min_matched_weight; // linear version
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

                    // MATCHING CONDITION
                    if (match_quality > MATCH_QUALITY)
                        bmatched = true;
                }
            }
            l++;
        }
        k++;
    }

    if (best_matched_regions > 0)
    {
        LOG4CXX_DEBUG(logger, " vs. model " << model->object_ID << "." << model->view_ID << " = " << best_matched_regions << " cors - q = " << best_quality);
        LOG4CXX_DEBUG(logger, "                 (lmk weight, model weight, color sim, shape sim) = " << (int)best_lmk_weight << "%, " << (int)best_mod_weight << "%, " << best_anchor_match.color_similarity << ", " <<  best_anchor_match.shape_similarity << ")");
    }

    match->quality = best_quality;
    match->lmk_matched_weight = best_lmk_weight;
    match->mod_matched_weight = best_mod_weight;
    match->lowest_similarity = MIN (best_anchor_match.color_similarity, best_anchor_match.shape_similarity);

    return (bmatched);
} 




// This function checks the local coherence of two matched regions through an exhaustive comparison of their corresponding neighbours.
// It returns a matrix with all the obtained similarities to be used for finding region correspondences.
void Matching2::checkLocalCoherence(Body& oBody, Model& oModel, st_anchor_match& anchor_match)
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



bool Matching2::compareRegions(Body& oBody, Model& oModel, st_anchor_match& anchor_match)
{
    LOG4CXX_TRACE(logger, "Matching2.compareRegions");
    
    bool similar = false;
    float anchor_rotation;
    float dist_color, color_similarity, shape_similarity;

    // get orientation difference
    if (oBody.getOrientation() != Shape::UNDEFINED_ORIENTATION && oModel.getOrientation() != Shape::UNDEFINED_ORIENTATION)
    {
        anchor_rotation = maty::Angle::inLimits(oBody.getOrientation() - oModel.getOrientation());
    }
    else             
        anchor_rotation = 0;

    oHSVEssence.update(oBody.getHSV());
    dist_color = oHSVEssence.compare(oModel.getHSV());
    color_similarity = 1.0 - (dist_color/max_dist_color);

    shape_similarity = MIN (lmk_region->shape_factor, model_region->shape_factor) / MAX (lmk_region->shape_factor, model_region->shape_factor);		

    // SIMILARITY: color & shape	 
    if  (color_similarity > SIMILARITY && shape_similarity > SIMILARITY)			
            similar = true;

    anchor_match->rotation = anchor_rotation;
    anchor_match->color_similarity = color_similarity;
    anchor_match->shape_similarity = shape_similarity;
    return (similar);
} 



// This function compares a pair of neighbours based on position, color and scale. It returns true if the neighbours are similar, otherwise returns false.
// Filter: 			module, angle, scale
// Similarity: 		color
bool Matching2::compareNeighbours (st_neighbour* lmk_neighbour, st_neighbour* model_neighbour, float anchor_rotation, float* similarities)
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
void Matching2::findCorrespondences ()
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


// This function searches for a specif region ID in a given list. It returns true if found or false otherwise. 
// When found, the item is removed from the list.
bool Matching2::findRegionInList (CvSeq* seq_avoid_regions, int search_id)
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
void Matching2::computeMatchedWeights (st_model* model, float* plmk_matched_weight, float* pmod_matched_weight)
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
void Matching2::unmarkLandmarkRegions ()
{
    int num_regions = oLandmark->getNumRegions();

    // clear all marks
    for (int i=0; i < num_regions; i++)
    {
            oLandmark->getRegion(i)->matched = 0;
    }
}
				
 

// This function marks matched landmark regions (for debugging purpose)
void Matching2::markLandmarkRegions (CvSeq* seq_aux)
{
	int correspondence[2];
		
	while (seq_aux->total > 0)
	{
		cvSeqPop (seq_aux, &correspondence);
		oLandmark->getRegion(correspondence[0])->matched = 2;
	}													
}



void Matching2::getBestCandidates(std::vector<st_match>& seq_matches)
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
		
		matched_object = match->matched_object;
		
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
CvSeq* Matching2::getListCandidateMatches ()
{			
	return (seq_candidate_matches);
}  
}
