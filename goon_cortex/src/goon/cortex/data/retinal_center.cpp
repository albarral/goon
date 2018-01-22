/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "retinal_center.h"


namespace goon
{
// constructor
RetinalCenter::RetinalCenter (CvSize image_size)
{
#ifdef DEBUG_MODE
	cout << " init - InitRetinalCenter" << endl;
#endif	 		
	
	retinal_storage = cvCreateMemStorage(0);
	
	seq_active_regions = cvCreateSeq(CV_32SC1, sizeof(CvSeq),sizeof(int), retinal_storage);

	for (int i=0; i<MAX_REGIONS; i++)
	{
            regions[i].mask = cvCreateImage (image_size, IPL_DEPTH_8U,1);
            cvZero (regions[i].mask);
            regions[i].seq_subregions = cvCreateSeq(CV_32SC1, sizeof(CvSeq),sizeof(int), retinal_storage);
	}
	
#ifdef DEBUG_MODE
	cout << " end - InitRetinalCenter" << endl;
#endif
}


// destructor
RetinalCenter::~RetinalCenter()
{
#ifdef DEBUG_MODE
	cout << " init - EndRetinalCenter" << endl;
#endif

	// release memory storage 
	cvReleaseMemStorage (&retinal_storage);
  
	// release regions 
	for (int i=0; i<MAX_REGIONS; i++)
	{
		cvReleaseImage (&(regions[i].mask));
		cvReleaseMat (&(regions[i].mat_grid));
	}

#ifdef DEBUG_MODE
	cout << " end - EndRetinalCenter" << endl;
#endif
}


void RetinalCenter::initGrids (int grid_rows, int grid_cols)
{
#ifdef DEBUG_MODE
	cout << " init - InitRetinalGrids" << endl;
#endif

	for (int i=0; i<MAX_REGIONS; i++)
	{
		regions[i].mat_grid = cvCreateMat (grid_rows, grid_cols, CV_32SC1);
		cvZero (regions[i].mat_grid);
	}

#ifdef DEBUG_MODE
	cout << " end - InitRetinalGrids" << endl;
#endif
}

  
  
// This functions clears the specified region. 
void RetinalCenter::clearRegion (int i)
{	
#ifdef DEBUG_MODE
	cout << " init - ClearRegion" << endl;
#endif
        st_region *region = &(regions[i]);
	region->pixels = 0;	
	if (region->window.width > 0 && region->window.height > 0)
	{
		cvSetImageROI (region->mask, region->window);
		cvZero (region->mask);
		cvResetImageROI(region->mask);		
	}
	cvZero (region->mat_grid);
	
#ifdef DEBUG_MODE
	cout << " end - ClearRegion" << endl;
#endif
}  


st_region* RetinalCenter::getRegions () {return regions;}

// Acces a specified region structure
st_region* RetinalCenter::getRegion (int i) {return &(regions[i]);}



 void RetinalCenter::addActiveRegion (int reg_id)
{
    cvSeqPush (seq_active_regions, &reg_id);
}


// Return the Id of the retinal region in the specified position of the active regions list
int RetinalCenter::getActiveRegion (int pos)
{
    return (*(int*)cvGetSeqElem (seq_active_regions, pos));
}


int RetinalCenter::getNumActiveRegions ()
{
    return (seq_active_regions->total);
}


void RetinalCenter::clearListActiveRegions ()
{
	cvClearSeq (seq_active_regions);
}


// This function sorts the list of active regions by size in decreasing order
void RetinalCenter::sortActiveRegionsBySize ()
{
    sortRegionsBySize (seq_active_regions);
}

// This function sorts the given list of regions by size in decreasing order
void RetinalCenter::sortRegionsBySize (CvSeq* seq_regions)
{
    cvSeqSort (seq_regions, sortBySize, regions);
}


 // This function sorts regions by size in decreasing order
int RetinalCenter::sortBySize (const void* _a, const void* _b, void* userdata)
{
	int a = *(int*)_a;
	int b = *(int*)_b;
	st_region* regs = (st_region*)userdata;

        int dif = regs[b].pixels - regs[a].pixels;
	return(dif);
}
}
