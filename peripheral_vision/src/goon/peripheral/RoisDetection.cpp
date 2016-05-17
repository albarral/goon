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


void RoisDetection::detectROIs(std::vector<Region>& listRegions)
{
    LOG4CXX_INFO(logger, "detect ROIs");
        
    // if ROIs & regions exist, try matching them
    if (listROIs.size()>0 && listRegions.size()>0)
    {
        matchRois2Regions(listRegions);
    }    
    else
        LOG4CXX_WARN(logger, "Skipped matching! No ROIs or no regions");
            
    // create new ROIs for orphan regions
    handleOrphanRegions(listRegions);
    
    // remove obsolete ROIs
    removeObsoleteRois();
}


// try to match ROIs and regions (based on color & overlap)
void RoisDetection::matchRois2Regions(std::vector<Region>& listRegions)
{
    int totalTouches = 0;
    
    LOG4CXX_DEBUG(logger, "try matching ROIs and regions");
        
    // create overlap matrix
    matOverlaps = cv::Mat_<int>(listROIs.size(), listRegions.size());  
    matOverlaps.setTo(0);           

    // for each ROI
    int numRoi = 0;
    for (ROI& oROI : listROIs)
    {              
        // reset ROI's matching info
        oROI.clearMatchingInfo();

        // check the regions to which the ROI responds
        int numTouched = compareRoi2Regions(numRoi, oROI, listRegions);

        if (numTouched > 0)
        {
            oROI.setTouchedRegions(numTouched);                
            totalTouches += numTouched;
        }
        numRoi++;

        LOG4CXX_DEBUG(logger, "ROI " << oROI.getID() << ": " << numTouched << " touches");
    }

    // compute correspondences between ROIs and regions
    if (totalTouches > 0)
        findBestMatches(listRegions);
}

// Checks how the given ROI responds to regions. 
// A ROI responds to a region if it has its same color and its mask is overlapped by the region (minimum of 10% required)
// The number of positive responses is returned.
int RoisDetection::compareRoi2Regions(int row, ROI& oROI, std::vector<Region>& listRegions)
{
    float HSV_SAME = oHSVColor.getDistSameColor();
    int overlapArea = 0;
    int numMatches = 0;
    int minOverlapArea = minOverlapFraction * oROI.getArea();

    LOG4CXX_DEBUG(logger, "matchRoi2Regions ... ROI " << oROI.getID());
           
    cv::Mat matRow = matOverlaps.row(row);                

    int numReg = 0;
    // compare with each region
    for (Region& oRegion : listRegions)    
    {
        // if region and ROI have same color
        if (oHSVColor.getDistance(oROI.getHSV(), oRegion.getHSV(), HSVColor::eSAME_COLOR) < HSV_SAME)
        {
            // checks overlap ROI-region
            overlapArea = oROI.computeOverlap(oRegion);
            if (overlapArea > minOverlapArea)
            {                
                matRow.at<int>(numReg) = overlapArea;
                LOG4CXX_DEBUG(logger, "touched region " << oRegion.getID() << " - overlap area = " << overlapArea);
                numMatches++;
            }
        }
        numReg++;
    }
    
    return numMatches;
}

// Establishes correspondences between ROIs and regions
// Iteratively searches for the maximum overlaps, each of them yielding a new correspondence
void RoisDetection::findBestMatches(std::vector<Region>& listRegions)
{    
    double maxVal; 
    cv::Point maxLoc;
    int row, col;
    std::list<ROI>::iterator it_ROI;
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
            row = maxLoc.y;     // rows are ROIs
            col = maxLoc.x;      // columns are regions               
            
            // mark correspondence
            it_ROI = listROIs.begin(); 
            std::advance(it_ROI, row);  // access element in std::list
            it_ROI->setCapturedRegion(col);
            Region& oRegion = listRegions.at(col);
            oRegion.setCaptured(true);            
            
            LOG4CXX_DEBUG(logger, "ROI " << it_ROI->getID() << " captured region " << col);
            
            // eliminate references to this ROI and region in matOverlaps
            cv::Mat matRow = matOverlaps.row(row);                
            cv::Mat matCol = matOverlaps.col(col);                
            matRow.setTo(0);
            matCol.setTo(0);            
        }                
        // if nothing found, finish search
        else
            bsearch = false;
    }
}


// create new ROIs for uncaptured regions    
void RoisDetection::handleOrphanRegions(std::vector<Region>& listRegions)
{
    int n=0;
    for (Region& oRegion : listRegions)    
    {
        if (!oRegion.isCaptured())
        {
            // generate new ROI
            int ID = oIDPool.takeOne();
            ROI oROI;
            oROI.setID(ID);
            // set the blob part
            oROI Blob::operator= oRegion;
            //oROI Blob::operator= (Blob)oRegion;
            // set the body part
            //oROI Body::operator=(oRegion); 
            oROI = (Body)oRegion; 
            // mark as matched    
            oROI.setCapturedRegion(n);
            // mark region as captured
            oRegion.setCaptured(true);

            // and add it to the list of ROIs
            listROIs.push_back(oROI);
            LOG4CXX_DEBUG(logger, "New ROI " << oROI.getID() << " for region " << oRegion.getID());          
        }
        n++;
    }
}
    
// Eliminate obsolete ROIs    
void RoisDetection::removeObsoleteRois()
{
    std::list<ROI>::iterator it_ROI = listROIs.begin();
    // walk list of ROIs
    while (it_ROI != listROIs.end())
    {
        // if ROI has no capture, it's obsolete
        if (it_ROI->getCapturedRegion() == -1)
        {
            // make ROI ID available again
            int ID = it_ROI->getID();
            oIDPool.freeOne(ID);
            // remove the ROI from list
            it_ROI = listROIs.erase(it_ROI);

            LOG4CXX_TRACE(logger, "eliminate !!!" << ID);
        }
        else
            it_ROI++;
    }                  
}


//void RoisDetection::getNumbers (int* merged_units, int* eliminated_units)
//{
//    *merged_units = merges;
//    *eliminated_units = eliminations;
//}




}




