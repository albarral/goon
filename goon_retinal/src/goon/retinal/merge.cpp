/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <list>

#include "goon/retinal/merge.h"
#include "goon/retinal/ConfigRetinal.h"
#include <goon/data/base/region.h>
#include "goon/features/color/rgb_color.h"
#include <maty/math/distance.h>

using namespace log4cxx;

namespace goon
{
LoggerPtr Merge::logger(Logger::getLogger("goon.retinal"));

// Constructor
Merge::Merge()
{        
    ConfigRetinal oConfigRetinal;
    proximityGAP = oConfigRetinal.getMergeProximityGap();   // default gap = 10 pixels
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
    cv::Rect window1;       // expanded window of region 1
    cv::Rect window2;       // expanded window of region 2
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
        // expand region1's window
        window1 = it_region1->getWindow() + expansion;

        // check against the rest of regions
        std::list<Region>::iterator it_region2 = it_region1;
        it_region2++;        
        while (it_region2 != list_end)
        {		
            // expand region2's window
            window2 = it_region2->getWindow() + expansion;
            // compute intersection of both windows
            intersection = window1 & window2;

            // if windows overlap
            if (intersection.width != 0  &&  intersection.height != 0)
            {
                LOG4CXX_DEBUG(logger, "check regions " << it_region1->getID());
                // if bodies are mergeable
                if (checkMergeableBodies(*it_region1, *it_region2, intersection))
                {
                    it_region1->setMerge(true);
                    it_region2->setMerge(true);

                    // make a cross in the proximity matrix (with symmetry)
                    mat_proximity.at<uchar>(it_region1->getID(), it_region2->getID()) = 1;
                    mat_proximity.at<uchar>(it_region2->getID(), it_region1->getID()) = 1;                    
                }
                        
                // and region grids overlap ...
//                if (checkGridsOverlap(it_region1->getMassGrid(), it_region2->getMassGrid()))
//                {
//                    // and color is the same -> mark regions for merging
//                    if (maty::Distance::getEuclidean3s(it_region1->getRGB(), it_region2->getRGB()) < SQR_SAME) 
//                    {
//                        it_region1->setMerge(true);
//                        it_region2->setMerge(true);
//                        
//                        // make a cross in the proximity matrix (with symmetry)
//                        mat_proximity.at<uchar>(it_region1->getID(), it_region2->getID()) = 1;
//                        mat_proximity.at<uchar>(it_region2->getID(), it_region1->getID()) = 1;
//                    }
//                }			
            } // end if		

            it_region2++;
        } // end for

        it_region1++;
    }
}


// Checks whether two region grids overlap or not.
bool Merge::checkGridsOverlap(cv::Mat& mat_grid1, cv::Mat& mat_grid2)
{
    bool boverlap = false;
    int rows = mat_grid1.rows;
    int cols = mat_grid1.cols;
    
    for (int i=0; i<rows; i++)
    {
        ushort* row1 = mat_grid1.ptr<ushort>(i);
        ushort* row2 = mat_grid2.ptr<ushort>(i);

        for (int j=0; j<cols; j++)
        {
            // if grid nodes overlap, exit loop
            if (row1[j] != 0 && row2[j] != 0)
            {
                boverlap = true;
                break;                
            }
        }	
        
        if (boverlap) break;
    }
    
    return (boverlap);
}


bool Merge::checkMergeableBodies(ColorBody& oBody1, ColorBody& oBody2, cv::Rect& window)
{
    // get grid intersection window
    cv::Rect gridWindow = oGrid.computeGridWindow(window);
    
    // body1 grids   
    cv::Mat massGrid1 = oBody1.getMassGrid()(gridWindow);
    cv::Mat rgbGrid1 = oBody1.getRGBGrid()(gridWindow);
    // body2 grids
    cv::Mat massGrid2 = oBody2.getMassGrid()(gridWindow);
    cv::Mat rgbGrid2 = oBody2.getRGBGrid()(gridWindow);

    float SQR_SAME = RGBColor::getSqrSameDist();
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
                bmerge = maty::Distance::getEuclidean3s(rgbGrid1.at<cv::Vec3f>(i, j), rgbGrid2.at<cv::Vec3f>(i, j)) < SQR_SAME;
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
