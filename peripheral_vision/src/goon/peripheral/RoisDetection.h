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
#include <goon/data/base/roi.h>
#include <goon/data/base/region.h>
#include "goon/utils/hsv_color.h"


namespace goon
{
// Module for the detection of ROIs, regions of interest that represent physical regions in the scene.
// ROIS are associated to segmented regions, but are living entities with an own history and movement.
class RoisDetection
{
private:
    static log4cxx::LoggerPtr logger;
    // param
    float minOverlapFraction; // minimum ROI overlap (fraction) required to consider a positive matching
    // vars
    std::list<ROI> listROIs;      // list of ROIS 
    int eliminations;
    HSVColor oHSVColor;
    IDPool oIDPool;             // pool of IDs for the ROIs
    cv::Mat matOverlaps;      // matrix of ROI overlaps (pixels) by regions (rows are ROIs, columns are Regions, CV_32SC1)


public:
    RoisDetection();
    ~RoisDetection ();

    // returns a reference to the list of ROIs
    std::list<ROI>& getListROIs () {return listROIs;};

    void detectROIs (std::vector<Region>& listRegions);
    
    void setMinOverlapFraction(float value) {minOverlapFraction = value;};

//    void getNumbers (int* merged_units, int* eliminated_units);

private:
    // try to match ROIs and regions (based on color & overlap)
    void matchRois2Regions(std::vector<Region>& listRegions);
    
    // Checks how the given ROI responds to regions. 
    // The number of positive responses is returned
    int compareRoi2Regions(int row, ROI& oROI, std::vector<Region>& listRegions);
    
    // Establishes correspondences between ROIs and regions
    void findBestMatches(std::vector<Region>& listRegions);
    
    // create new ROIs for uncaptured regions
    void handleOrphanRegions(std::vector<Region>& listRegions);
    
    // eliminate absent ROIs
    void removeObsoleteRois();

    // This function creates a new ROI with the given sampled region.
    void generateNewROI(Region& oRegion) ;

};

}  

#endif
