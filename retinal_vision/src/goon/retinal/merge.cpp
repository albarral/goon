/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>

#include "goon/retinal/merge.h"
#include "goon/retinal/ConfigRetinal.h"
#include <goon/data/base/region.h>
#include "goon/utils/rgb_color.h"
#include <goon/utils/distance.h>

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
    LOG4CXX_DEBUG(logger, "init ...");

    // create the collection mask 
    maskCollection = cv::Mat::zeros(img_h, img_w, CV_8UC1); 
}

// This function merges all adjacent regions with similar color.
int Merge::doMerge (Retina& oRetina)
{
    int created_regions;
	
    // check which regions can be merged
    checkProximityMerge(oRetina);

    // Merge all mergeable regions by proximity
    created_regions = mergeRegions(oRetina);

    LOG4CXX_INFO(logger, "Created regions = " << created_regions);

    return(created_regions);
}
					

// ****************************************  FUNCTION: CheckProximityMerge  ***************************************

// This function checks if there are nearby regions with similar color that can be merged. 
void Merge::checkProximityMerge (Retina& oRetina)
{
    cv::Rect window1;       // expanded window of region 1
    cv::Rect window2;       // expanded window of region 2
    cv::Rect wintersection;          // intersection window
    cv::Size2i expansion;
    float SQR_SAME = RGBColor::getSqrSameDist();
    
    expansion.width = expansion.height = proximityGAP;    
    
    int num_regions = oRetina.getNumRegions();
    mat_proximity = cv::Mat::zeros(num_regions, num_regions, CV_8UC1);    

    std::vector<Region>::iterator it_region1 = oRetina.getListRegions().begin();
    std::vector<Region>::iterator list_end = oRetina.getListRegions().end();
    
    // for each region in the list
    while (it_region1 != list_end)
    {
        // expand region1's window
        window1 = it_region1->getWindow() + expansion;

        // check against the rest of regions
        std::vector<Region>::iterator it_region2 = it_region1;
        it_region2++;        
        while (it_region2 != list_end)
        {		
            // expand region2's window
            window2 = it_region2->getWindow() + expansion;
            // compute intersection of both windows
            wintersection = window1 & window2;

            // if windows overlap
            if (wintersection.width != 0  &&  wintersection.height != 0)
            {
                // and region grids overlap ...
                if (checkGridsOverlap(it_region1->getGrid(), it_region2->getGrid()))
                {
                    // and color is the same -> mark regions for merging
                    if (Distance::getEuclidean3s(it_region1->getRGB(), it_region2->getRGB()) < SQR_SAME) 
                    {
                        it_region1->setMerge(true);
                        it_region2->setMerge(true);
                        
                        // make a cross in the proximity matrix (with symmetry)
                        mat_proximity.at<uchar>(it_region1->getID(), it_region2->getID()) = 1;
                        mat_proximity.at<uchar>(it_region2->getID(), it_region1->getID()) = 1;
                    }
                }			
            } // end if		

            it_region2++;
        } // end for

        it_region1++;
    }
}


// Checks whether two region grids overlap or not.
bool Merge::checkGridsOverlap (cv::Mat& mat_grid1, cv::Mat& mat_grid2)
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


// This function merges similar nearby regions into new regions. 
// Merged regions become subregions and new regions are collections.
int Merge::mergeRegions (Retina& oRetina)
{
    int num_collections = 0;

   // for each region in the list
    for (Region& oRegion: oRetina.getListRegions()) 
    {
        // if region is to be merged & has simple type (not absorbed by other collection)
        if (oRegion.is2Merge() && oRegion.getType() == Region::eREG_SIMPLE)
        {		
            // create a new collection
            createCollection(oRegion, oRetina);            
            
            num_collections++;            
        } 
    } 

    return(num_collections);  
}


// Creates a collection by merging a set of regions into the specified base region.
void Merge::createCollection (Region& oBaseRegion, Retina& oRetina)
{  
    LOG4CXX_DEBUG(logger, "new collection " << oBaseRegion.getID());
    
    // reset collection mask and list
    maskCollection.setTo(0);
    setCollectionRegions.clear();
    
    // the base region becomes a collection
    oBaseRegion.setType(Region::eREG_COLLECTION);

    // start collection with the base region
    setCollectionRegions.insert(oBaseRegion.getID()); // otherwise will be reflexively included
    updateCollectionMask(oBaseRegion);
            
    // expand the list with more regions
    checkRegions2Merge(oBaseRegion.getID());

   // for each region in the list
    for (int regionID: setCollectionRegions) 
    {
        Region& oRegion = oRetina.getRegion(regionID);               
        
        // add a new region to the collection (avoid self merging)
        if (oRegion.getID() != oBaseRegion.getID())
        {		
            LOG4CXX_DEBUG(logger, "add region " << oRegion.getID());
            // merge blob info (color, covs, window, mass))
            oBaseRegion.merge(oRegion);
            // grow collection mask (with original window)
            updateCollectionMask(oRegion);                    
            // and mark it as merged
            oRegion.setType(Region::eREG_MERGED);
        }
    }
    
    oBaseRegion.createMask(maskCollection, oBaseRegion.getWindow());
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

void Merge::updateCollectionMask(Region& oRegion)
{
    cv::Mat roiCollection;
    // set roi and copy data
    roiCollection = maskCollection(oRegion.getWindow());
    roiCollection = oRegion.getMask();    
}

}
