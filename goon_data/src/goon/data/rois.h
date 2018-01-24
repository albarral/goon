#ifndef __GOON_DATA_ROIS_H
#define __GOON_DATA_ROIS_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>
#include <map>

#include "goon/data/base/roi.h"

namespace goon 
{
class Rois
{
private:
    std::list<ROI> listROIs;      // list of ROIS (lists allow fast sorting & removals, not as vectors)
    std::map<int, int> mapROIs;     // map: ROI.ID - ROI position in listROIs
    
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

    // rebuilds mapROIs in coherence with present listROIs
    void remap();
    
    // returns the ROI with the specified ID
    ROI* getROIByID(int ID);
    // returns the ROI at the specified position in the list
    ROI* getROIByIndex(int pos);
    
    // check if the specified roi exists
    bool doesROIExist(int roiID);   

private:
    // get ROI position in list (using the map)
    int getROIPosition(int roiID);    
};

}	
#endif
