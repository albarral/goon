/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>

#include "goon/retinal/merge.h"
#include "goon/retinal/ConfigRetinal.h"
#include <goon/data/base/region.h>
#include "goon/features/color/HSVEssence.h"
#include "goon/features/color/rgb_color.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr Merge::logger(Logger::getLogger("goon.retinal"));

// Constructor
Merge::Merge()
{        
    ConfigRetinal oConfigRetinal;
    proximityGAP = oConfigRetinal.getMergeProximityGap();   // default gap = 10 pixels
    // same similarity values as in retinal segmentation
    oColorSimilarity.setRGBSimilarity(RGBColor::getSqrSameDist());
    oColorSimilarity.setHSVSimilarity(oConfigRetinal.getColorEssenceHSVSimilarity());    
}


// Destructor
Merge::~Merge()
{
}

void Merge::init(int img_w, int img_h)
{        
    ConfigRetinal oConfigRetinal;
    oGrid.setSize(img_w, img_h, oConfigRetinal.getGridStep());    
}

// This function merges all adjacent regions with similar color.
int Merge::doMerge(Retina& oRetina)
{
    // check which regions can be merged
    checkProximityMerge(oRetina);

    // Merge all mergeable regions by proximity
    int collections = mergeRegions(oRetina);

    LOG4CXX_DEBUG(logger, "collections = " << collections);

    return collections;
}
					

// ****************************************  FUNCTION: CheckProximityMerge  ***************************************

// This function checks if there are nearby regions with similar color that can be merged. 
void Merge::checkProximityMerge(Retina& oRetina)
{
    cv::Rect expWindow1;       // expanded window of region 1
    cv::Rect expWindow2;       // expanded window of region 2
    cv::Rect intersection;          // intersection window
    cv::Size2i expansion;
    
    expansion.width = expansion.height = proximityGAP;    
    
    int num_regions = oRetina.getNumRegions();
    mat_proximity = cv::Mat::zeros(num_regions, num_regions, CV_8UC1);    

    std::list<Region>::iterator it_region1 = oRetina.getListRegions().begin();
    std::list<Region>::iterator list_end = oRetina.getListRegions().end();
    
    // for each region in the list
    while (it_region1 != list_end)
    {
        LOG4CXX_DEBUG(logger, "check region " << it_region1->getID());
        // expand region1's window
        expWindow1 = it_region1->getWindow() + expansion;

        // check against the rest of regions
        std::list<Region>::iterator it_region2 = it_region1;
        it_region2++;        
        while (it_region2 != list_end)
        {		
            // expand region2's window
            expWindow2 = it_region2->getWindow() + expansion;
            // compute intersection of both windows
            intersection = expWindow1 & expWindow2;

            // if windows overlap
            if (intersection.width != 0  &&  intersection.height != 0)
            {
                // if bodies are mergeable
                if (checkMergeableBodies(*it_region1, *it_region2, intersection))
                {
                    it_region1->setMerge(true);
                    it_region2->setMerge(true);

                    // make a cross in the proximity matrix (with symmetry)
                    mat_proximity.at<uchar>(it_region1->getID(), it_region2->getID()) = 1;
                    mat_proximity.at<uchar>(it_region2->getID(), it_region1->getID()) = 1;                    
                    LOG4CXX_DEBUG(logger, "merged with " << it_region2->getID());
                }                        
            } // end if		

            it_region2++;
        } // end for

        it_region1++;
    }
}


bool Merge::checkMergeableBodies(ColorBody& oBody1, ColorBody& oBody2, cv::Rect& intersectionWindow)
{
    // if bodies don't overlap, they can't be merged
    int overlap = oBody1.computeOverlap(oBody2);
    if (overlap == 0)
        return false;

    LOG4CXX_DEBUG(logger, "overlap = " << overlap);

    // get grid intersection window
    cv::Rect gridWindow = oGrid.computeGridWindow(intersectionWindow);
    
    // body1 grids   
    cv::Mat massGrid1 = oBody1.getMassGrid()(gridWindow);
    cv::Mat rgbGrid1 = oBody1.getRGBGrid()(gridWindow);
    // body2 grids
    cv::Mat massGrid2 = oBody2.getMassGrid()(gridWindow);
    cv::Mat rgbGrid2 = oBody2.getRGBGrid()(gridWindow);

    HSVEssence oHSVEssence;
    oHSVEssence.update(oBody1.getHSV());                

    bool bmerge = false;
    // checks node by node ...
    for (int i=0; i<gridWindow.height; i++)
    {
        for (int j=0; j<gridWindow.width; j++)
        {
            // if nodes overlap
            if (massGrid1.at<ushort>(i, j) != 0 && massGrid2.at<ushort>(i, j) != 0)
            {                  
                // and have same color              
                bmerge =  oColorSimilarity.checkSameColor(rgbGrid1.at<cv::Vec3f>(i, j), rgbGrid2.at<cv::Vec3f>(i, j), oHSVEssence, oBody2.getHSV());
                //bmerge = maty::Distance::getEuclidean3s(rgbGrid1.at<cv::Vec3f>(i, j), rgbGrid2.at<cv::Vec3f>(i, j)) < SQR_SAME;
                if (bmerge)
                    break;
            }                        
        }
        if (bmerge)
            break;        
    }

    return bmerge;
}

// This function merges similar nearby regions into new regions. 
// Merged regions become subregions and new regions are collections.
int Merge::mergeRegions(Retina& oRetina)
{
    int num_collections = 0;

   // for each region in the list
    for (Region& oRegion: oRetina.getListRegions()) 
    {
        // if region is to be merged & has simple type (not absorbed by other collection)
        if (oRegion.is2Merge() && oRegion.getType() == Region::eREG_SIMPLE)
        {		
            // create a new collection
            createCollection2(oRegion, oRetina);            
            
            num_collections++;            
        } 
    } 

    return(num_collections);  
}


void Merge::createCollection2(Region& oBaseRegion, Retina& oRetina)
{  
    LOG4CXX_TRACE(logger, "new collection " << oBaseRegion.getID());
    
    // the base region becomes a collection
    oBaseRegion.setType(Region::eREG_COLLECTION);

    // build collection list (using a set to reject reflexive inclusions)
    setCollectionRegions.clear();
    setCollectionRegions.insert(oBaseRegion.getID()); 
    checkRegions2Merge(oBaseRegion.getID());

   // for each region in the list
    int i = 0;
    for (int regionID: setCollectionRegions) 
    {
        // skip base region
        if (i==0) 
        {
            i++;
            continue;
        }
        
        Region& oRegion = oRetina.getRegion(regionID);                       
        LOG4CXX_TRACE(logger, "add region " << oRegion.getID());
        // merge it 
        oBaseRegion.merge(oRegion);
        // and mark it as merged
        oRegion.setType(Region::eREG_MERGED);        
        i++;
    }
    
    LOG4CXX_TRACE(logger, "collection \n" << oBaseRegion.toString());
}


void Merge::checkRegions2Merge(int baseID)
{      
    int presize;
    cv::Mat matRow = mat_proximity.row(baseID);      
    
    // check which regions are to be merged with the base one
    for (int j=0; j<mat_proximity.cols; j++)
    {
        if (matRow.at<uchar>(j) == 1)
        {
            presize = setCollectionRegions.size();
            setCollectionRegions.insert(j);
            // if region added to collection (not rejected for repeated) recall this function for each region to merge
            if (setCollectionRegions.size() > presize)
                checkRegions2Merge(j);
        }
    }	
}

}
