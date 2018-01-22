/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include <stdio.h>
#include <math.h>
#include <opencv2/core/core.hpp>
  
#include "goon/cortex/analysis/characterization.h"
#include "goon/features/shape/shape.h"
#include "maty/math/distance.h"
#include "goon/cortex/data/regions.h"
#include "goon/cortex/config/vanal_defines.h"
#include "goon/cortex/config/vision_defines.h"

using namespace log4cxx;
namespace goon
{
LoggerPtr Characterization::logger(Logger::getLogger("goon.cortex.characterization"));

// constructor
Characterization::Characterization (RetinalCenter* oRetinalCenter, VisualCenter* oVisualCenter)
{
#ifdef DEBUG_MODE
	cout << " init - InitCharacterization" << endl;
#endif

        mRetinalCenter = oRetinalCenter;
        mVisualCenter = oVisualCenter;
        oLandmark = mVisualCenter->getLandmarkV1();

#ifdef DEBUG_MODE
	cout << " end - InitCharacterization" << endl;
#endif
}


// This function computes the landmark's shape, centroid, scale and orientation.
void Characterization::checkGlobalObject ()
{
#ifdef DEBUG_MODE
	cout << " init - analyseGlobalObject" << endl;
#endif
        Shape oShape;

        oLandmark->setScale(oLandmark->getArea()*100.0 / mVisualCenter->getImageArea());

        oShape.computeShape (oLandmark->getMask(), oLandmark->getWindow());

        oLandmark->setCentroid(oShape.getCentroid());

        // shape factor (rotation invariant)
        oLandmark->setShapeFactor(oShape.getShapeFactor());

        oLandmark->setOrientation(oShape.getAngle());

#ifdef DEBUG_MODE
	cout << " end - analyseGlobalObject" << endl;
#endif
}


// This function builds the internal structure of the landmark based in its composing regions. 
// The smaller regions are rejected and only the relevant ones are characterized, using color, shape and context information.
// The function returns true if the structure could be built, or false otherwise.
bool Characterization::checkObjectDetails ()
{
#ifdef DEBUG_MODE
	cout << " init - BuildLandmarkStructure" << endl;
#endif
	int filter_size;

        oLandmark->clearRegions();
	//mVisualCenter->clearLandmarkContext();
	
	filter_size = LANDMARK_DETAIL * oLandmark->getArea();
	
	filterRetinalRegions (filter_size);
		
	characterizeRegions ();
				  		
#ifdef DEBUG_MODE
	cout << " end - BuildLandmarkStructure" << endl;
#endif	
	return (oLandmark->getNumRegions() > 0);
}


// This function fixes the characterized landmark version in the visual center.
void Characterization::fixLandmark ()
{
	mVisualCenter->transferV1();
}


// This function checks the list of focused retinal regions selecting the most relevant ones for the landmark's characterization.
// It also sorts them by size in decreasing order.
void Characterization::filterRetinalRegions (int min_size)
{
#ifdef DEBUG_MODE
	cout << " init - FilterLandmarkRegions" << endl;
#endif
	int reg_id, i;

	i = 0;
	while (i <  mVisualCenter->getNumFormingRegions())
	{
		reg_id = mVisualCenter->getFormingRegion(i);

		if (mRetinalCenter->getRegion(reg_id)->pixels < min_size)
		{
			mVisualCenter->removeFormingRegion(i);
		}
		else 
			i++;
	}		

	// then sort regions by weight
        mRetinalCenter->sortRegionsBySize(mVisualCenter->getListFormingRegions());
			
#ifdef DEBUG_MODE
	cout << " end - FilterLandmarkRegions" << endl;
#endif
}
				 
	
// ****************************************  FUNCTION: CharacterizeRegions ***************************************
	
// This function characterizes each landmark region with color, shape and context information.
void Characterization::characterizeRegions ()
{
#ifdef DEBUG_MODE
	cout << " init - CharacterizeRegions" << endl;
#endif
	int reg_id;
	st_region* region;
	st_lmk_region* lmk_region;
        int max_regions;
        int lmkArea;
        Shape oShape;
        int* pcentroid;
        float* pcovs;

	max_regions = MIN (mVisualCenter->getNumFormingRegions(), REGIONS_PER_LMK);
	oLandmark->setNumRegions(max_regions);

        lmkArea = oLandmark->getArea();

	for (int i=0; i<max_regions; i++)
	{
            lmk_region = oLandmark->getRegion(i);

            mVisualCenter->popFormingRegion(&reg_id);
            region = mRetinalCenter->getRegion(reg_id);

            lmk_region->ID = region->ID;
            lmk_region->type = region->type;
            lmk_region->weight = region->pixels*100.0 / lmkArea;
            for (int j=0; j<3; j++)
                    lmk_region->color[j] = region->color[j];

            oShape.computeShape (region->mask, &(region->window));

            pcentroid = oShape.getCentroid();
            pcovs = oShape.getCovariances();
            lmk_region->centroid[0] = pcentroid[0];
            lmk_region->centroid[1] = pcentroid[1];
            lmk_region->covs[0] = pcovs[0];
            lmk_region->covs[1] = pcovs[1];
            lmk_region->covs[2] = pcovs[2];

            // shape factor (rotation invariant)
            lmk_region->shape_factor = oShape.getShapeFactor();

            lmk_region->orientation = oShape.getAngle();
	}
	
	// CHARACTERIZE LOCAL NEIGHBOURHOODS 
	
	for (int j=0; j<max_regions; j++)
	{
            characterizeNeighbours (j);
	}		
	  	
	showLandmarkFeatures ();

#ifdef DEBUG_MODE
	cout << " end - CharacterizeRegions" << endl;
#endif
}
					

// ****************************************  FUNCTION: CharacterizeNeighbours ***************************************

// This function characterizes the neighbourhood of a base region.
// If the base region is collection its subregions must be avoided, and viceversa
void Characterization::characterizeNeighbours (int base_region)
{
#ifdef DEBUG_MODE
	cout << " init - CharacterizeNeighbours" << endl;
#endif
	int numNeighbours = 0;
	bool bsubregion_control;
        st_lmk_region *baseRegion, *neighbourRegion;

        baseRegion = oLandmark->getRegion(base_region);

	// if base region is collection or subregion, subregions control must be done
	if (baseRegion->type == eREG_SIMPLE)
		bsubregion_control = false;
	else
		bsubregion_control = true;
	
	for (int i=0; i < oLandmark->getNumRegions(); i++)
	{	
		if (i == base_region)
			continue;

                neighbourRegion = oLandmark->getRegion(i);

		// if regions are related avoid neighbour
		if (bsubregion_control && neighbourRegion->type != eREG_SIMPLE)
		{ 
			// CheckSubregionRelation()
			if (checkSubregionRelation (baseRegion, neighbourRegion))
				continue;
		}
			
		// SetNeighbourData()
		setNeighbourData (baseRegion, numNeighbours, neighbourRegion, i);
		numNeighbours++;
	}

	baseRegion->num_neighbours = numNeighbours;

#ifdef DEBUG_MODE
	cout << " end  - CharacterizeNeighbours" << endl;
#endif
}


// ****************************************  FUNCTION: CheckSubregionRelation ***************************************

// This function checks if any of the input regions is subregion of the other. It returns true if the regions are related, or false otherwise.
bool Characterization::checkSubregionRelation (st_lmk_region* lmk_region1, st_lmk_region* lmk_region2)
{
#ifdef DEBUG_MODE
	cout << " init - CheckSubregionRelation" << endl;
#endif
	bool related = false;
					
	// check father-son relation ...
	if (lmk_region1->type == eREG_COLLECTION && lmk_region2->type == eREG_MERGED)
	{
		for (int i=0; i<lmk_region1->seq_subregions->total; i++)
		{		  		
			if (lmk_region2->ID == *(int*)cvGetSeqElem(lmk_region1->seq_subregions, i))
			{
				related = true;
				break;
			}
		}							
	}
	// or son-father relation
	else 	if (lmk_region1->type == eREG_MERGED && lmk_region2->type == eREG_COLLECTION)
	{
		for (int i=0; i<lmk_region2->seq_subregions->total; i++)
		{		  		
			if (lmk_region1->ID == *(int*)cvGetSeqElem(lmk_region2->seq_subregions, i))
			{
				related = true;
				break;
			}
		}									
	}

#ifdef DEBUG_MODE
	cout << " end  - CheckSubregionRelation" << endl;
#endif
	
	return (related);
}


// ****************************************  FUNCTION: SetNeighbourData ***************************************

// This function obtains relative data from the neighbours of a given landmark region 
// tM10 = M10 - xM00
// tM01 = M01 - yM00
void Characterization::setNeighbourData (st_lmk_region* lmk_region1, int n, st_lmk_region* lmk_region2, int list_position)
{
#ifdef DEBUG_MODE
	cout << " init - SetNeighbourData" << endl;
#endif
	float xdif, ydif;

	lmk_region1->neighbours[n].ID = list_position;
		
	lmk_region1->neighbours[n].color[0] = lmk_region2->color[0];
	lmk_region1->neighbours[n].color[1] = lmk_region2->color[1];
	lmk_region1->neighbours[n].color[2] = lmk_region2->color[2];
	
	lmk_region1->neighbours[n].rel_weight = lmk_region2->weight / lmk_region1->weight;
	
	// relative position in polar coordinates
	xdif = lmk_region2->centroid[0] - lmk_region1->centroid[0];
	ydif = lmk_region2->centroid[1] - lmk_region1->centroid[1]; 
	// DistMahalanobis ()
	lmk_region1->neighbours[n].rel_position[0] = sqrt(Distance::getMahalanobisXY (lmk_region2->centroid, lmk_region1->centroid, lmk_region1->covs)); // affine invariant
	lmk_region1->neighbours[n].rel_position[1] = atan2(-ydif, xdif)*180/M_PI; // sign of y changed because image Y axis faces down
	
	lmk_region1->neighbours[n].shape_factor = lmk_region2->shape_factor;
	lmk_region1->neighbours[n].orientation = lmk_region2->orientation;

#ifdef DEBUG_MODE
	cout << " end  - SetNeighbourData" << endl;
#endif
}


// This function prints landmarks features
void Characterization::showLandmarkFeatures ()
{
	st_lmk_region* lmk_region;
        int num_regions = oLandmark->getNumRegions();
  	
        LOG4CXX_DEBUG(logger, "LANDMARK (" << num_regions << " regions)");
        LOG4CXX_DEBUG(logger, "         descriptors (type, weight, shape_factor, orientation):");
	
	for (int i=0; i < num_regions; i++)
	{
            lmk_region = oLandmark->getRegion(i);

            showRegionFeatures(lmk_region, i);
	}	
	
}


// This function prints region's features
void Characterization::showRegionFeatures (st_lmk_region* lmk_region, int num)
{
#ifdef DEBUG_MODE
	cout << " init - ShowRegionFeatures" << endl;
#endif
  
        LOG4CXX_DEBUG(logger, "         R" << num << " - id " << lmk_region->ID);
        LOG4CXX_DEBUG(logger, "          " << lmk_region->type << ", " << lmk_region->weight << ", " << lmk_region->shape_factor << ", " << (int)lmk_region->orientation << " deg");
        LOG4CXX_DEBUG(logger, "          hsv = " << (int)lmk_region->color[0] << ", " << (int)lmk_region->color[1] << ", " << (int)lmk_region->color[2]);
		
	// if collection, show subregions
	if (lmk_region->type == eREG_COLLECTION)
	{
            for (int i=0; i<lmk_region->seq_subregions->total; i++)
                LOG4CXX_DEBUG(logger, "          subregion " << *(int*)cvGetSeqElem(lmk_region->seq_subregions, i));
	}	
	
	// neighbours' features
	if (lmk_region->num_neighbours > 0)
	{

            LOG4CXX_DEBUG(logger, "          neighbours (rel_weight, module, angle):");
            for (int i=0; i < lmk_region->num_neighbours; i++)
           {
                st_neighbour* neighbour = &(lmk_region->neighbours[i]);
                LOG4CXX_DEBUG(logger, "          id " << neighbour->ID << " (" << neighbour->rel_weight << ", " << neighbour->rel_position[0] << ", " << neighbour->rel_position[1] << ")");
            }
	}
	
#ifdef DEBUG_MODE
	cout << " end  - ShowRegionFeatures" << endl;
#endif
}
}

