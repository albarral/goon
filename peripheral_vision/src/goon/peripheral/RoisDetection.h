#ifndef __GOON_PERIPHERAL_ROIS_DETECTION_H
#define __GOON_PERIPHERAL_ROIS_DETECTION_H

/***************************************************************************
 *   Copyright (C) 2011 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <vector>
#include <log4cxx/logger.h>
#include "opencv2/core/core.hpp"

#include "goon/peripheral/IDPool.h"
#include "goon/data/retina.h"
#include "goon/data/rois.h"
#include <goon/data/base/roi.h>
#include <goon/data/base/region.h>
#include "goon/utils/hsv_color.h"


namespace goon
{
// Module for the detection of ROIs, regions of interest that represent physical regions in the scene.
// ROIS are associated to segmented regions, but are living entities with an own history and movement.
class RoisDetection
{
// structure to handle ROI-Region matchings
struct st_match
{
    int roiID;
    int regionID;
    float confidence;    
};    

private:
    static log4cxx::LoggerPtr logger;
    // param
    float minOverlapFraction; // minimum ROI overlap (fraction) required to consider a positive matching
    // vars
    Retina* pRetina;        // pointer to retina
    Rois* pROIs;            // pointer to ROIs
    int eliminations;
    HSVColor oHSVColor;
    IDPool oIDPool;             // pool of IDs for the ROIs
    cv::Mat matOverlaps;    // matrix of ROI overlaps (ROIS x regions), stores overlap amounts (in pixels) 
    std::vector<st_match> listMatches;  // list of ROI-Region matchings 


public:
    RoisDetection();
    ~RoisDetection ();

    void detectROIs(Retina& oRetina, Rois& oROIs);
    
    void setMinOverlapFraction(float value) {minOverlapFraction = value;};

    int getEliminations() {return eliminations;};

private:
    // prepare ROIs for a new detection process
    void prepareDetection();
    
    // try to match ROIs and regions (based on color & overlap)
    void matchROIs2Regions();
    
    // update matched ROIs to follow their regions
    void updateMatchedROIs();
    
    // Checks how the given ROI responds to regions. 
    // The number of positive responses is returned
    int compareROI2Regions(int row, ROI& oROI, std::list<Region>& listRegions);
    
    // Establishes correspondences between ROIs and regions
    void findBestMatches();
    // adds a new match to the list of matches
    void newMatch(int roiID, int regionID, float confidence);
    
    // create new ROIs for unmatched regions
    void handleOrphanRegions();
    // adds a new ROI to the list of ROIs
    void newROI(Region& oRegion);
    
    // eliminate absent ROIs
    void removeObsoleteRois();    
};

}  

#endif
