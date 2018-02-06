/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "goon/cortex/recognition/Matching2.h"
#include "goon/features/shape/shape.h"
#include "maty/math/Angle.h"
#include "maty/utils/Matrix.h"
							
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
    max_dist_color = 3.0;
    maxRotation = 90.0;
    reqSimilarity = 3.0;
    reqQuality = 100;    
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
    st_match match;					
	
    // for each model
    for (ObjectModel& oObjectModel : listObjectModels)
    {		
        // compare object and model
        // if matching quality is high enough, add new match candidate 
        if (compareObject2Model(oObject, oObjectModel, match) >= reqQuality)
        {
            seq_candidate_matches.push_back(match);
        }
    } 

    // if various candidates -> filter the best 
//    if (seq_candidate_matches.size() > 1)
//        filterCandidates();

    LOG4CXX_DEBUG(logger, "best_candidates = " << seq_candidate_matches.size());

    return (!seq_candidate_matches.empty());
}


float Matching2::compareObject2Model(Object& oObject, ObjectModel& oObjectModel, st_match& match)
{
    LOG4CXX_TRACE(logger, "Matching2.compareObject2Model");

    // similarity matrix
    int rows = oObject.getSubBodies().size();
    int cols = oObjectModel.getSubModels().size();
    mat_similarity = cv::Mat::zeros(rows, cols, CV_32FC(5));  // depth 5 (eSIM_DIM)

    // compare object subodies with object model submodels
    int row=0;
    for (Body& oBody : oObject.getSubBodies())
    {
        cv::Mat matRow = mat_similarity.row(row);        
        int col = 0;
        for (Model& oModel : oObjectModel.getSubModels()) 
        {
            // fill similarity matrix
            matRow.at<Vec5f>(col) = compareRegions(oBody, oModel);
            col++;
        }
        row++;
    }

    // establish region correspondences
    findCorrespondences();
    
    // compute quality of the matching
    float q = computeMatchingQuality(oObject, oObjectModel);

    // compute fractions of matched object and model
    cv::Vec2f matchedFractions = computeMatchedFractions(oObject, oObjectModel);    

    match.modelID = oObjectModel.getID();
    match.quality = q;
    match.objectMatchedFraction = matchedFractions[0];
    match.modelMatchedFraction = matchedFractions[1];

    return q;
} 


Matching2::Vec5f Matching2::compareRegions(Body& oBody, Model& oModel)
{
    LOG4CXX_TRACE(logger, "Matching2.compareRegions");
    
    Vec5f similarities;
    
    // orientation similarity
    float angle1 = oBody.getOrientation();
    float angle2 = oModel.getOrientation();
    bool boriented1 = (angle1 != Shape::UNDEFINED_ORIENTATION);
    bool boriented2 = (angle2 != Shape::UNDEFINED_ORIENTATION);
    float rotation;
    // both oriented, compute rotation    
    if (boriented1 && boriented2)
    {
        rotation = maty::Angle::cyclicDifference(angle1 - angle2);
    }
    // if only one oriented, set max rotation
    else if (boriented1 != boriented2)            
        rotation = Shape::UNDEFINED_ORIENTATION;
    // if none oriented, zero rotation
    else
        rotation = 0.0;
    similarities[eSIM_ANGLE] = 1.0 - fabs(rotation)/maxRotation;
    
    // color similarity
    oHSVEssence.update(oBody.getHSV());
    float dist_color = oHSVEssence.compare(oModel.getHSV());
    similarities[eSIM_COLOR] = 1.0 - (dist_color/max_dist_color);

    // shape similarity
    float shape1 = oBody.getShapeFactor();
    float shape2 = oModel.getShapeFactor();
    // shape sim = smaller factor / bigger factor
    similarities[eSIM_SHAPE] = (shape1 > shape2 ? shape2 / shape1 : shape1 / shape2);

    // weight similarity
    int mass1 = oBody.getMass();
    int mass2 = oModel.getMass();
    // weight sim = smaller mass / bigger mass
    similarities[eSIM_WEIGHT] = (mass1 > mass2 ? (float)mass2 / mass1 : (float)mass1 / mass2);
    
    // total similarity (sum of similarities)
    similarities[eSIM_TOTAL] = similarities[eSIM_ANGLE] + similarities[eSIM_COLOR] + similarities[eSIM_SHAPE] + similarities[eSIM_WEIGHT];

    return similarities;
} 


void Matching2::findCorrespondences()
{	
    LOG4CXX_TRACE(logger, "Matching2.findCorrespondences");
    
    // clear correspondences
    seq_correspondences.clear();
    
    // extract total similarity channel
    std::vector<cv::Mat> matChannels;
    cv::split(mat_similarity, matChannels);    

    // establish correspondences between the most similar region-region pairs
    maty::Matrix::getCorrespondences(matChannels[eSIM_TOTAL], reqSimilarity, seq_correspondences);
}  


float Matching2::computeMatchingQuality(Object& oObject, ObjectModel& oObjectModel)
{
    LOG4CXX_TRACE(logger, "Matching2.computeMatchingQuality");

    float quality = 0.0;
    for (cv::Vec2i& correspondence : seq_correspondences)
    {
        Vec5f& similarities = mat_similarity.at<Vec5f>(correspondence[0], correspondence[1]);        
        // add total similarities of all correspondences
        quality += similarities[eSIM_TOTAL];        
    }

    return quality;
}
 
cv::Vec2f Matching2::computeMatchedFractions(Object& oObject, ObjectModel& oObjectModel)
{
    LOG4CXX_TRACE(logger, "Matching2.computeMatchedFractions");

    cv::Vec2f fractions(0.0, 0.0);

    for (cv::Vec2i& correspondence : seq_correspondences)
    {
        Body& oBody = oObject.getSubBodies()[correspondence[0]];
        Model& oModel = oObjectModel.getSubModels()[correspondence[1]];
        
        fractions[0] += oBody.getMass();
        fractions[1] += oModel.getMass();
    }
    
    fractions[0] = fractions[0] / oObject.getMass();
    fractions[1] = fractions[1] / oObjectModel.getMass();
    
    return fractions;
}

//
//void Matching2::filterCandidates(std::vector<st_match>& seq_matches)
//{	
//    LOG4CXX_TRACE(logger, "Matching2.filterCandidates");
//
//    CvSeq* seq_candidates = cvCreateSeq( CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_candidate), storage);
//	st_candidate *candidate;
//	st_candidate new_candidate;
//	st_match *match;
//	int matched_object;
//	bool bcandidate_found;
//
//	// FIND WINNER VIEWS OF BEST CANDIDATE OBJECTS
//	
//	// for each candidate match
//	for (int i=0; i < seq_matches->total; i++)
//	{
//		match = (st_match*)cvGetSeqElem (seq_matches, i);		
//		
//		matched_object = match->modelID;
//		
//		// check if matched object is already a candidate
//		bcandidate_found = false;
//		for (int j=0; j < seq_candidates->total; j++)
//		{
//			candidate = (st_candidate*)cvGetSeqElem (seq_candidates, j);		
//			
//			if (matched_object == candidate->object)
//			{
//				bcandidate_found = true;
//				break;
//			}
//		}
//		
//		// if matched object was a candidate
//		if (bcandidate_found)
//		{	
//			// update it only if new view was better matched
//			if (match->quality > candidate->quality)
//			{
//				candidate->quality = match->quality;
//				candidate->match_position = i;
//			}
//		}
//		// otherwise add it as new candidate
//		else
//		{
//			new_candidate.object = matched_object;
//			new_candidate.quality = match->quality;
//			new_candidate.match_position = i;
//			
//			cvSeqPush (seq_candidates, &new_candidate);
//		}		
//	}	// end for
//		
//	// Put the winner views in seq_candidate_matches	
//	for (int k=0; k < seq_candidates->total; k++)
//	{
//		candidate = (st_candidate*)cvGetSeqElem (seq_candidates, k);		
//
//		match = (st_match*)cvGetSeqElem (seq_matches, candidate->match_position);		
//				
//		cvSeqPush (seq_candidate_matches, match); 	
//	}	
//		
//	cvClearSeq (seq_candidates);
//		
//#ifdef DEBUG_MODE
//	cout << " end - GetBestCandidates" << endl;	
//#endif
//}

}
