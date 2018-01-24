/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdexcept>      // std::out_of_range

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
    clear();
}

void Rois::clear()
{
    listROIs.clear();
    mapROIs.clear();
}

void Rois::addROI (ROI& oRoi)
{
    listROIs.push_back(oRoi);
}

void Rois::remap()
{
    // clear map
    mapROIs.clear();
    
    // walk list and create associated map
    std::list<ROI>::iterator it_ROI = listROIs.begin();
    std::list<ROI>::iterator it_end = listROIs.end();    
    int pos = 0;
    while (it_ROI != it_end)
    {
        mapROIs.emplace(it_ROI->getID(), pos);        
        it_ROI++;
        pos++;
    }
    
}

ROI* Rois::getROIByID(int ID)
{
    // first we get the mapped position
    int pos = getROIPosition(ID);
    // then we access the ROI
    return getROIByIndex(pos);
}

ROI* Rois::getROIByIndex(int pos)
{
    // if position exists, return ROI pointer
    if (pos >= 0 && pos < listROIs.size())
    {
        std::list<ROI>::iterator it_ROI = listROIs.begin();
        std::advance(it_ROI, pos);
        return &(*it_ROI);    
    }
    // otherwise, return 0
    else
        return 0;
}

// This function checks if the specified roi is still active or not.
bool Rois::doesROIExist(int roiID)
{
    return (getROIPosition(roiID) != -1);
}

int Rois::getROIPosition(int roiID)
{
    try
    {
        // get mapped position of given ROI
        return mapROIs.at(roiID);
    }    
    catch (const std::out_of_range& oor) 
    {
        // not found
        return -1;
    }
}

}


