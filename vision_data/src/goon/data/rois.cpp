/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "goon/data/rois.h"

	
namespace goon 
{
// constructor
Rois::Rois()
{
}

// destructor
Rois::~Rois ()
{
}

void Rois::setListROIs(std::vector<ROI>& listROIs)
{
    vec_rois = listROIs;    
}

void Rois::clear()
{
    vec_rois.clear();
}

void Rois::addROI (ROI& oRoi)
{
    vec_rois.push_back(oRoi);
}


// This function checks if the specified roi is still active or not.
bool Rois::isROIStillActive (int roiID)
{
    bool bactive = false;
	
    // check if there's any roi with the specified ID
    std::vector<ROI>::iterator it_roi;
    for (it_roi = vec_rois.begin(); it_roi != vec_rois.end(); it_roi++)
    {
        if (it_roi->getID() == roiID)
        {
            bactive = true;
            break;
        }
    }
			
    return (bactive);
}
}


