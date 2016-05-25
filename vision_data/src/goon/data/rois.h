#ifndef __GOON_DATA_ROIS_H
#define __GOON_DATA_ROIS_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>

#include "goon/data/base/roi.h"

namespace goon 
{
class Rois
{
private:
    std::list<ROI> listROIs;      // list of ROIS (lists allow fast sorting & removals, not as vectors)
    
public:
    Rois ();
    ~Rois();

    // Returns the list of rois
    std::list<ROI>& getList() {return listROIs;};

    int getNumROIs() {return listROIs.size();};
    
    // clears the list of rois
    void clear();
    
    // adds a new roi to the list
    void addROI(ROI& oRoi);

    // returns the ROI with the specified ID
    ROI& getROI(int ID);
    
    // Checks if the specified roi is still active.
    bool isROIStillActive(int roiID);   
};

}	
#endif
