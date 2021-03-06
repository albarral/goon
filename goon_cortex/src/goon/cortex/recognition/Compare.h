#ifndef __GOON_CORTEX_COMPARE_H
#define __GOON_CORTEX_COMPARE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <vector>
#include <log4cxx/logger.h>

#include <opencv2/core/core.hpp>

#include "goon/data/cortex/Model.h"
#include "goon/data/cortex/ObjectModel.h"
#include "goon/features/color/HSVEssence.h"

namespace goon
{
class Compare
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
    float colorTolerance;   // tolerance for color similarity (degrees)
    float angleTolerance;   // tolerance for orientation similarity (degrees)
    float reqSimilarity;    // required similarity to consider a region correspondence
    // result        
    float quality;              // quality of the matching 
    float maxQuality;        // max possible value of the quality (depends on compared models)   
    float matchedFraction1;     // matched fraction of model 1
    float matchedFraction2;     // matched fraction of model 2
    // logic
    HSVEssence oHSVEssence; // utility for color similarity
    cv::Mat mat_similarity;     // similarity matrix (with depth = eSIM_DIM)
    std::vector<cv::Vec2i> seq_correspondences;     // region correspondences between models
    
public:
    Compare();
    ~Compare();
    
    void setColorSensitivity(float value) {colorTolerance = value;}
    //void setShapeSensitivity(float value) {shapeSense = value;}
    void setOrientationSensitivity(float value)  {angleTolerance = value;}
    //void setWeightSensitivity(float value) {weightSense = value;}
    
    float getQuality() {return quality;};
    float getMaxPossibleQuality() {return maxQuality;};
    float getMatchedFration1() {return matchedFraction1;}
    float getMatchedFration2() {return matchedFraction2;}

    // compares two object models in a region-region basis, it returns the matching quality
    float compareObjectModels(ObjectModel& oObjectModel1, ObjectModel& oObjectModel2);
            
    std::string showCorrespondences();
    
private:
    // compares two models (regions) based on color, shape, weight and orientation
    // returns a similarity vector
    Vec5f compareModels(Model& oModel1, Model& oModel2);
    
    // establish correspondences between the model regions (using the similarity matrix)
    void findCorrespondences();
    
    // computes a quality measure for the comparison of both object models
    void computeMatchingQuality();

    // computes the matched fractions of both object models
    void computeMatchedFractions(ObjectModel& oObjectModel1, ObjectModel& oObjectModel2);
};
}
#endif
