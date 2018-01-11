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
#include "maty/math/Distance2.h"

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
					

// This function checks if there are nearby regions with similar color that can be merged. 
void Merge::checkProximityMerge(Retina& oRetina)
{    
    int num_regions = oRetina.getNumRegions();
    mat_proximity = cv::Mat::zeros(num_regions, num_regions, CV_8UC1);    

    std::list<Region>::iterator it_region1 = oRetina.getListRegions().begin();
    std::list<Region>::iterator list_end = oRetina.getListRegions().end();
    
    // for each region in the list
    while (it_region1 != list_end)
    {
        // compute region1's border mask
        cv::Mat maskBorder1 = it_region1->computeBorderMask();
        cv::Rect& window1 = it_region1->getWindow();

        // check against the rest of regions
        std::list<Region>::iterator it_region2 = it_region1;
        it_region2++;        
        while (it_region2 != list_end)
        {	
            float separation = maty::Distance2::getWindowsSeparation(window1, it_region2->getWindow());

            // if windows are bordering
            if (separation < 2)
            {
                // check if region masks are also bordering
                int borderSize = it_region2->computeOverlap(maskBorder1, window1);
                
                // if regions have touching borders, check if the can be merged
                if (borderSize > 0)
                {                    
                    // check local color similarity
                    if (checkLocalSimilarity(*it_region1, *it_region2))
                    {
                        it_region1->setMerge(true);
                        it_region2->setMerge(true);

                        // make a cross in the proximity matrix (with symmetry)
                        mat_proximity.at<uchar>(it_region1->getID(), it_region2->getID()) = 1;
                        mat_proximity.at<uchar>(it_region2->getID(), it_region1->getID()) = 1;                    
                        LOG4CXX_DEBUG(logger, "merged " << it_region1->getID() << " + " << it_region2->getID());
                        LOG4CXX_DEBUG(logger, "border size = " << borderSize);
                    }
                }
            } // end if		

            it_region2++;
        } // end for

        it_region1++;
    }
}


bool Merge::checkLocalSimilarity(ColorBody& oBody1, ColorBody& oBody2)
{
    // get intersection window
    cv::Rect intersectionWindow = oBody1.getWindow() & oBody2.getWindow();
    // and its grid intersection
    cv::Rect gridWindow = oGrid.computeGridWindow(intersectionWindow);
    
    // body1 grids   
    cv::Mat massGrid1 = oBody1.getMassGrid()(gridWindow);
    cv::Mat rgbGrid1 = oBody1.getRGBGrid()(gridWindow);
    // body2 grids
    cv::Mat massGrid2 = oBody2.getMassGrid()(gridWindow);
    cv::Mat rgbGrid2 = oBody2.getRGBGrid()(gridWindow);

    HSVEssence oHSVEssence;
    oHSVEssence.update(oBody1.getHSV());                

    bool bsimilar = false;
    // check local nodes
    for (int i=0; i<gridWindow.height; i++)
    {
        for (int j=0; j<gridWindow.width; j++)
        {
            // if local nodes overlap
            if (massGrid1.at<ushort>(i, j) != 0 && massGrid2.at<ushort>(i, j) != 0)
            {                  
                // and have same color              
                bsimilar =  oColorSimilarity.checkSameColor(rgbGrid1.at<cv::Vec3f>(i, j), rgbGrid2.at<cv::Vec3f>(i, j), oHSVEssence, oBody2.getHSV());
                if (bsimilar)
                    break;
            }                        
        }
        if (bsimilar)
            break;        
    }
        
    return bsimilar;
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
