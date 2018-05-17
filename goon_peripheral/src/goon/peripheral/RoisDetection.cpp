/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h> 		

#include "goon/peripheral/RoisDetection.h"
#include "goon/features/BodyOverlap.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr RoisDetection::logger(Logger::getLogger("goon.peripheral"));

// constructor
RoisDetection::RoisDetection ()
{              
    minOverlapFraction = 0.10;     // 10% of ROI overlap required
}


//destructor
RoisDetection::~RoisDetection ()
{    
}


void RoisDetection::detectROIs(Retina& oRetina, Rois& oROIs, int millis)
{
    LOG4CXX_DEBUG(logger, "detect ROIs");
        
    pRetina = &oRetina;
    pROIs = &oROIs;
    eliminations = 0;
    
    // prepares ROIs for a new detection
    prepareDetection();
    
    // try matching ROIs & regions 
    if (pROIs->getNumROIs()>0 && pRetina->getNumRegions()>0)
    {
        matchROIs2Regions();
        
        updateMatchedROIs(millis);
    }    
            
    // create ROIs for orphan regions (regions with no associated ROI)
    handleOrphanRegions();
    
    // remove invalid ROIs (ROIs that represent no region anymore)
    pROIs->removeInvalidRois();
    
    // remap ROIs
    pROIs->updateRoisMap();
}

// reset values for new detection process
void RoisDetection::prepareDetection()
{
    listMatches.clear();
    
    // walk list of ROIs        
    for (ROI& oROI : pROIs->getList())
        oROI.setMatched(false);
}

// try to match ROIs and regions (based on color & overlap)
void RoisDetection::matchROIs2Regions()
{
    int totalTouches = 0;
    
    LOG4CXX_DEBUG(logger, "try matching ROIs and regions");
        
    std::list<Region>& listRegions = pRetina->getListRegions();
    std::list<ROI>& listROIs = pROIs->getList();
            
    // create overlap matrix (ROIS x regions)
    matOverlaps = cv::Mat::zeros(listROIs.size(), listRegions.size(), CV_32S);
    
    // for each ROI (or row)
    int indexROI = 0;
    for (ROI& oROI : listROIs)
    {              
        // check the regions to which the ROI responds
        int numTouched = compareROI2Regions(indexROI, oROI, listRegions);

        if (numTouched > 0)
            totalTouches += numTouched;

        indexROI++;

        LOG4CXX_DEBUG(logger, "ROI " << oROI.getID() << ": " << numTouched << " touches");
    }

    // compute correspondences between ROIs and regions
    if (totalTouches > 0)
        findBestMatches();
}


// try to match ROIs and regions (based on overlap & color)
//void RoisDetection::matchROIs2Regions2()
//{
//    LOG4CXX_DEBUG(logger, "RoisDetection::matchROIs2Regions2");
//        
//    float HSV_SAME = oHSVColor.getDistSameColor();    
//    std::list<Region>& listRegions = pRetina->getListRegions();
//    std::list<ROI>& listROIs = pROIs->getList();
//    
//    // clear matches list
//    listMatches2.clear();
//    
//    BodyOverlap oBodyUtils;
//    // compute overlaps (rois vs regions)
//    oBodyUtils.computeBodiesOverlaps(listROIs, listRegions);
//    // find overlap correspondences
//    int numCorrepondences = oBodyUtils.findOverlapCorrespondences();
//    
//    // if found, check matching colors
//    if (numCorrepondences > 0)
//    {
//        LOG4CXX_DEBUG(logger, "RoisDetection::matchROIs2Regions2: overlap correspondences = " << numCorrepondences);        
//        std::vector<cv::Vec2i>& listCorrespondences = oBodyUtils.getCorrespondences();
//        // for each correspondence
//        for (cv::Vec2i& correspondence : listCorrespondences)
//        {
//            // check color similarity
//            ROI* pROI = pROIs->getROIByIndex(correspondence[0]);
//            Region* pRegion = pRetina->getRegionByIndex(correspondence[1]);
//            // if both elements exist (the normal thing)
//            if (pROI != 0 && pRegion != 0)
//            {
//                // if region and ROI have same color, they match
//                if (oHSVColor.getDistance(pROI->getHSV(), pRegion->getHSV(), HSVColor::eSAME_COLOR) < HSV_SAME)
//                {
//                    pROI->setMatched(true);
//                    pRegion->setMatched(true);                    
//                    // add new match (roi ID, region ID)
//                    cv::Vec2i match(pROI->getID(), pRegion->getID()); 
//                    listMatches2.push_back(match);
//                }                
//            }
//            else
//                LOG4CXX_ERROR(logger, "RoisDetection::matchROIs2Regions2: roi-region correspondence not found");                        
//        }        
//    }
//    else
//        LOG4CXX_WARN(logger, "RoisDetection::matchROIs2Regions2: no correspondences");        
//}

// Checks how the given ROI responds to regions. 
// A ROI responds to a region if it has its same color and its mask is overlapped by the region (minimum of 10% required)
// The number of positive responses is returned.
int RoisDetection::compareROI2Regions(int row, ROI& oROI, std::list<Region>& listRegions)
{
    float HSV_SAME = oHSVColor.getDistSameColor();
    int overlapArea = 0;
    int numMatches = 0;
    int minOverlapArea = minOverlapFraction * oROI.getMass();

    LOG4CXX_DEBUG(logger, "matchRoi2Regions ... ROI " << oROI.getID());
           
    cv::Mat matRow = matOverlaps.row(row);                

    // for each region (or column)
    int indexRegion = 0;
    for (Region& oRegion : listRegions)    
    {
        // if region and ROI have same color
        if (oHSVColor.getDistance(oROI.getHSV(), oRegion.getHSV(), HSVColor::eSAME_COLOR) < HSV_SAME)
        {
            // checks overlap ROI-region
            overlapArea = oROI.computeOverlap(oRegion);
            if (overlapArea > minOverlapArea)
            {          
                // and stores it in matOverlaps
                matRow.at<int>(indexRegion) = overlapArea;
                LOG4CXX_DEBUG(logger, "touched region " << oRegion.getID() << " - overlap area = " << overlapArea);
                numMatches++;
            }
        }
        indexRegion++;
    }
    
    return numMatches;
}

// Establishes correspondences between ROIs and regions
// Iteratively searches for the maximum overlaps, each of them yielding a new correspondence
void RoisDetection::findBestMatches()
{    
    double maxVal; 
    cv::Point maxLoc;
    int indexROI, indexRegion;
    bool bsearch = true;

    LOG4CXX_DEBUG(logger, "findBestMatches ,,,");

    // iterate for each correspondence
    while (bsearch)
    {
        // find maximum overlap
        cv::minMaxLoc(matOverlaps, NULL, &maxVal, NULL, &maxLoc);
        
        // if new maximum found, set correspondence
        if (maxVal > 0)
        {
            indexROI = maxLoc.y;           // rows are ROIs
            indexRegion = maxLoc.x;      // columns are regions               
            
            // mark elements & add new match to the list
            ROI* pROI = pROIs->getROIByIndex(indexROI);
            Region* pRegion = pRetina->getRegionByIndex(indexRegion);
            // if both elements exist (the normal thing)
            if (pROI != 0 && pRegion != 0)
            {
                pROI->setMatched(true);
                pRegion->setMatched(true);
                // add new match
                newMatch(pROI->getID(), pRegion->getID(), maxVal);
                // and clear overlaps of both with others
                cv::Mat matRow = matOverlaps.row(indexROI);                
                cv::Mat matCol = matOverlaps.col(indexRegion);                
                matRow.setTo(0);
                matCol.setTo(0);            
                LOG4CXX_DEBUG(logger, "ROI " << pROI->getID() << " matched region " << pRegion->getID());
            }
            // otherwise, clear this wrong map node
            else
            {
                matOverlaps.at<int>(indexROI, indexRegion) = 0;                
            }
        }                
        // if nothing found, finish search
        else
            bsearch = false;
    }
}
    
// adds a new match to the list of matches
void RoisDetection::newMatch(int roiID, int regionID, float confidence)
{
    st_match match; 
    match.roiID = roiID;
    match.regionID = regionID;
    match.confidence = confidence;    
    listMatches.push_back(match);
}

// create new ROIs for unmatched regions    
void RoisDetection::handleOrphanRegions()
{
    int indexRegion=0;
    for (Region& oRegion : pRetina->getListRegions())    
    {
        if (!oRegion.isMatched())
        {
            // generate new ROI
            newROI(oRegion);
        }
        indexRegion++;
    }
}

// generate new ROI & adds it to list of ROIs
void RoisDetection::newROI(Region& oRegion)
{    
    ROI oROI;
    // set ROI body (associated region)
    oROI.setBody(oRegion);
    oROI.updateMotion(0);
    // mark as matched to avoid obsoletes removal    
    oROI.setMatched(true);     
    // and add it to the list of ROIs
    int ID = pROIs->addROI(oROI);    

    LOG4CXX_DEBUG(logger, "New ROI " << ID << " for region " << oRegion.getID());          
}


// update matched ROIs to follow their regions
void RoisDetection::updateMatchedROIs(int millis)
{
    for (st_match& match : listMatches)
    {
        ROI* pROI = pROIs->getROIByID(match.roiID);        
        Region* pRegion = pRetina->getRegionByID(match.regionID);
        // if both elements exist
        if (pROI != 0 && pRegion != 0)
        {
            // update ROIS's body with its perceived region
            pROI->setBody(*pRegion);
            // update ROI's motion & age
            pROI->updateMotion(millis);
            pROI->increaseAge();
        }
    }        
}

//void RoisDetection::updateMatchedROIs2(int millis)
//{
//    // walk matches list (roi ID, region ID)
//    for (cv::Vec2i& match : listMatches2)
//    {
//        ROI* pROI = pROIs->getROIByID(match[0]);        
//        Region* pRegion = pRetina->getRegionByID(match[1]);
//        // if both elements exist
//        if (pROI != 0 && pRegion != 0)
//        {
//            // update ROIS's body with its perceived region
//            pROI->setBody(*pRegion);
//            // update ROI's motion & age
//            pROI->updateMotion(millis);
//            pROI->increaseAge();
//        }
//    }        
//}

}
