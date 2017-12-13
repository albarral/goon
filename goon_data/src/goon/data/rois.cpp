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
    listROIs.clear();
}

void Rois::clear()
{
    listROIs.clear();
}

void Rois::addROI (ROI& oRoi)
{
    listROIs.push_back(oRoi);
}

ROI& Rois::getROI(int ID)
{
    // regions are ordered by ID
    std::list<ROI>::iterator it_ROI = listROIs.begin();
    std::advance(it_ROI, ID);
    
    return *it_ROI;
}

// This function checks if the specified roi is still active or not.
bool Rois::isROIStillActive (int roiID)
{
    bool bactive = false;
	
    // check if there's any roi with the specified ID
    for (ROI& oROI : listROIs)
    {
        if (oROI.getID() == roiID)
        {
            bactive = true;
            break;
        }
    }
			
    return (bactive);
}
}


