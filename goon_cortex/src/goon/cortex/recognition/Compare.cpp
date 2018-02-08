/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "goon/cortex/recognition/Compare.h"
#include "goon/features/shape/shape.h"
#include "maty/math/Angle.h"
#include "maty/utils/Matrix.h"
							
using namespace log4cxx;

namespace goon
{
LoggerPtr Compare::logger(Logger::getLogger("goon.cortex.recognition"));

// Constructor
Compare::Compare()
{
    colorSense = 30.0;
    //shapeSense = 1.0;
    angleSense = 45.0;
    //weightSense = 30.0;
    
    reqSimilarity = 3.0;    
}

Compare::~Compare ()
{
    seq_correspondences.clear();
}


float Compare::compareObjectModels(ObjectModel& oObjectModel1, ObjectModel& oObjectModel2)
{
    LOG4CXX_TRACE(logger, "Compare.compareObjectModels");

    // similarity matrix
    int rows = oObjectModel1.getSubModels().size();
    int cols = oObjectModel2.getSubModels().size();
    mat_similarity = cv::Mat::zeros(rows, cols, CV_32FC(eSIM_DIM));  // depth = eSIM_DIM (5)

    // compare submodels of both object models
    int row=0;
    for (Model& oModel1 : oObjectModel1.getSubModels())
    {
        cv::Mat matRow = mat_similarity.row(row);        
        int col = 0;
        for (Model& oModel2 : oObjectModel2.getSubModels()) 
        {
            // fill similarity matrix
            matRow.at<Vec5f>(col) = compareModels(oModel1, oModel2);
            col++;
        }
        row++;
    }

    // establish region correspondences
    findCorrespondences();
    
    // compute quality of the matching
    computeMatchingQuality();

    // compute matched fractions 
    computeMatchedFractions(oObjectModel1, oObjectModel2);    
    
    maxQuality = oObjectModel1.getSubModels().size() * eSIM_TOTAL;
    
    return quality;
} 


Compare::Vec5f Compare::compareModels(Model& oModel1, Model& oModel2)
{
    LOG4CXX_TRACE(logger, "Compare.compareModels");
        
    // orientation similarity
    float angle1 = oModel1.getOrientation();
    float angle2 = oModel2.getOrientation();
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
    
    float angleSim = 1.0 - fabs(rotation)/angleSense;
    if (angleSim < 0)
        angleSim = 0.0;
    
    // color similarity
    oHSVEssence.update(oModel1.getHSV());
    float dist_color = oHSVEssence.compare(oModel2.getHSV());
    float colorSim = 1.0 - dist_color/colorSense;
    if (colorSim < 0)
        colorSim = 0.0;

    // shape similarity
    float shape1 = oModel1.getShapeFactor();
    float shape2 = oModel2.getShapeFactor();
    // shape sim = smaller factor / bigger factor
    float shapeSim = (shape1 > shape2 ? shape2/shape1 : shape1/shape2);

    // weight similarity ( 1 - increase factor * max fraction)
    int mass1 = oModel1.getMass();
    int mass2 = oModel2.getMass();
    bool bgrow = (mass2 > mass1);
    float increaseFactor = bgrow ? (float)mass2/mass1 : (float)mass1/mass2;
    float maxFraction = bgrow ? (float)mass2/100 : (float)mass1/100;
    float weightSim = 1.0 - increaseFactor * maxFraction;
        
    // total similarity (sum of similarities)
    float totalSim = angleSim + colorSim + shapeSim + weightSim;
       
    return Vec5f(colorSim, shapeSim, weightSim, angleSim, totalSim);
} 


void Compare::findCorrespondences()
{	
    LOG4CXX_TRACE(logger, "Compare.findCorrespondences");
    
    // clear correspondences
    seq_correspondences.clear();
    
    // extract total similarity channel
    std::vector<cv::Mat> matChannels;
    cv::split(mat_similarity, matChannels);    

    // establish correspondences between the most similar region-region pairs
    maty::Matrix::getCorrespondences(matChannels[eSIM_TOTAL], reqSimilarity, seq_correspondences);
}  


void Compare::computeMatchingQuality()
{
    LOG4CXX_TRACE(logger, "Compare.computeMatchingQuality");

    quality = 0.0;
    for (cv::Vec2i& correspondence : seq_correspondences)
    {
        Vec5f& similarities = mat_similarity.at<Vec5f>(correspondence[0], correspondence[1]);        
        // add total similarities of all correspondences
        quality += similarities[eSIM_TOTAL];        
    }    
}
 
void Compare::computeMatchedFractions(ObjectModel& oObjectModel1, ObjectModel& oObjectModel2)
{
    LOG4CXX_TRACE(logger, "Compare.computeMatchedFractions");

    matchedFraction1 = 0.0;
    matchedFraction2 = 0.0;

    // for each correspondence, accumulate the masses of both matched regions
    for (cv::Vec2i& correspondence : seq_correspondences)
    {
        Model& oModel1 = oObjectModel1.getSubModels()[correspondence[0]];
        Model& oModel2 = oObjectModel2.getSubModels()[correspondence[1]];
        
        matchedFraction1 += oModel1.getMass();
        matchedFraction2 += oModel2.getMass();
    }
    
    matchedFraction1 = matchedFraction1 / oObjectModel1.getMass();
    matchedFraction2 = matchedFraction2 / oObjectModel2.getMass();
}

void Compare::showCorrespondences()
{
    LOG4CXX_INFO(logger, "model correspondences = " << seq_correspondences.size());
    for (cv::Vec2i& correspondence : seq_correspondences)
    {
        Vec5f& similarities = mat_similarity.at<Vec5f>(correspondence[0], correspondence[1]);

        std::string text1 = "regions " + std::to_string(correspondence[0]) + " & " + std::to_string(correspondence[1]) + 
                ": similarities = "; 
        
        std::string text2;
        for (int i=0; i<eSIM_DIM; i++)
            text2 += std::to_string(similarities[i]) + ", ";

        LOG4CXX_INFO(logger, text1 + text2);        
    }
}

}
