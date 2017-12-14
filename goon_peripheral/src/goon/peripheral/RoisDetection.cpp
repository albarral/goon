/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h> 		

#include "goon/peripheral/RoisDetection.h"

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


void RoisDetection::detectROIs(Retina& oRetina, Rois& oROIs)
{
    LOG4CXX_INFO(logger, "detect ROIs");
        
    pRetina = &oRetina;
    pROIs = &oROIs;
    eliminations = 0;
    
    // prepares ROIs for a new detection
    prepareDetection();
    
    // try matching only if ROIs & regions exist
    if (pROIs->getNumROIs()>0 && pRetina->getNumRegions()>0)
    {
        matchROIs2Regions();
        
        updateMatchedROIs();
    }    
            
    // create new ROIs for orphan regions
    handleOrphanRegions();
    
    // remove obsolete ROIs
    removeObsoleteRois();
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
            ROI& oROI = pROIs->getROI(indexROI);
            Region& oRegion = pRetina->getRegion(indexRegion);
            oROI.setMatched(true);
            oRegion.setMatched(true);
            newMatch(indexROI, indexRegion, maxVal);
            
            LOG4CXX_DEBUG(logger, "ROI " << oROI.getID() << " matched region " << indexRegion);
            
            // eliminate references to this ROI and region in matOverlaps
            cv::Mat matRow = matOverlaps.row(indexROI);                
            cv::Mat matCol = matOverlaps.col(indexRegion);                
            matRow.setTo(0);
            matCol.setTo(0);            
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
    int ID = oIDPool.takeOne();
    
    ROI oROI;
    oROI.setID(ID);
    oROI.setBody(oRegion);
    int pos[2] = {oRegion.getPos()[0], oRegion.getPos()[1]};
    oROI.getTransMove().init(pos);
    // mark as matched to avoid obsoletes removal    
    oROI.setMatched(true);     
    // and add it to the list of ROIs
    pROIs->addROI(oROI);    

    LOG4CXX_DEBUG(logger, "New ROI " << ID << " for region " << oRegion.getID());          
}


// update matched ROIs to follow their regions
void RoisDetection::updateMatchedROIs()
{
    for (st_match& match : listMatches)
    {
        ROI& oROI = pROIs->getROI(match.roiID);        
        Region& oRegion = pRetina->getRegion(match.regionID);

        oROI.setBody(oRegion);
        // update ROI's motion & age
        int pos[2] = {oRegion.getPos()[0], oRegion.getPos()[1]};        
        oROI.getTransMove().update(pos);
        oROI.increaseAge();
    }        
}

// Eliminate obsolete ROIs    
void RoisDetection::removeObsoleteRois()
{
    std::list<ROI>& listROIs = pROIs->getList();
    std::list<ROI>::iterator it_ROI = listROIs.begin();
    // walk list of ROIs
    while (it_ROI != listROIs.end())
    {
        // if ROI not matched, remove it
        if (!it_ROI->isMatched())
        {
            // make ROI ID available again
            int ID = it_ROI->getID();
            oIDPool.freeOne(ID);
            // remove the ROI from list
            it_ROI = listROIs.erase(it_ROI);
           
            eliminations++;
            LOG4CXX_TRACE(logger, "eliminate !!!" << ID);
        }
        else
            it_ROI++;
    }                  
}

}
