/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv/cv.h>

#include "goon/cortex/data/Landmark.h"


namespace goon
{
Landmark::Landmark (int w, int h)
{	

    storage = cvCreateMemStorage(0);

    mask = cv::Mat::zeros(h, w, CV_8UC1); 
    window = cvRect (0, 0, 0, 0);
    num_regions = 0;

        for (int i=0; i<REGIONS_PER_LMK; i++)
            lmk_regions[i].seq_subregions = cvCreateSeq(CV_32SC1, sizeof(CvSeq),sizeof(int), storage);
}

Landmark:: ~Landmark ()
{
	// release memory storage 
	cvReleaseMemStorage (&storage);  
}

void Landmark::clearMask()
{
    if (window.width > 0 && window.height > 0)
    {
            cv::Mat maskROI = mask(window);
            maskROI.setTo(0);
    }
}

void Landmark::addMask (cv::Mat& amask, cv::Rect& awindow)
{
    cv::Mat mask1 = mask(awindow);
    cv::Mat mask2 = amask(awindow);
    mask1 = mask1 | mask2;
}


void Landmark::setWindow(cv::Rect& awindow)
{
    window = awindow;
}

void Landmark::addWindow(cv::Rect& awindow)
{
    window = window | awindow;
}


void Landmark::increaseArea (int value) {area += value;}

void Landmark::setColor (float *value)
{
    color[0] = value[0];
    color[1] = value[1];
    color[2] = value[2];
}



void Landmark::setCentroid (int* value)
{
    centroid[0] = value[0];
    centroid[1] = value[1];
}

st_lmk_region* Landmark::getRegions () {return lmk_regions;}
st_lmk_region* Landmark::getRegion (int i) {return &(lmk_regions[i]);}

// Clears the regions of the landmark.
void Landmark::clearRegions ()
{
	// reset subregions sequences
	for (int i=0; i<num_regions; i++)
	{
		cvClearSeq (lmk_regions[i].seq_subregions);
	}

	num_regions = 0;
}
}