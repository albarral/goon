#ifndef __GOON_DATA_ROIS_H
#define __GOON_DATA_ROIS_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "goon/data/base/roi.h"

namespace goon 
{
class Rois
{
private:
    std::vector<ROI> vec_rois;          // vector of rois 
    
public:
    Rois ();
    ~Rois();

    // sets the ROIs list
    void setListROIs(std::vector<ROI>& listROIs);
    
    // Returns the list of rois
    std::vector<ROI>& getList () {return vec_rois;};

    int getNumROIs() {return vec_rois.size();};
    
    // clears the list of rois
    void clear();
    
    // adds a new roi to the list
    void addROI(ROI& oRoi);

    // Checks if the specified roi is still active.
    bool isROIStillActive(int roiID);   
};

}	
#endif
