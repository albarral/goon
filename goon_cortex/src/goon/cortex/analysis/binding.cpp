/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>

#include "goon/cortex/analysis/binding.h"
#include "maty/math/area.h"
#include "goon/cortex/config/vanal_defines.h"
#include "goon/cortex/config/vision_defines.h"
	

namespace goon
{
// constructor
Binding::Binding (RetinalCenter* oRetinalCenter, VisualCenter* oVisualCenter)
{
#ifdef DEBUG_MODE
	cout << " init - InitBinding" << endl;
#endif

        mRetinalCenter = oRetinalCenter;
        mVisualCenter = oVisualCenter;
        oLandmark = mVisualCenter->getLandmarkV1();

        joinObjectFraction = formObjectOverlapThreshold;        

#ifdef DEBUG_MODE
	cout << " end - InitBinding" << endl;
#endif
}


// destructor
Binding::~Binding()
{
}


// This function builds the landmark from the regions inside the roi's window.
// The landmark's mask is built from them.
void Binding::formObject (CvRect* roi_window)
{
#ifdef DEBUG_MODE
	cout << " init - formObject" << endl;
#endif
	st_region* region;
	int reg_id, maxSize;
        float overlap;
        int numActiveRegions = mRetinalCenter->getNumActiveRegions();

        oLandmark->setArea(0);

	// Reset landmark's mask
	oLandmark->clearMask();

	mVisualCenter->clearListFormingRegions();
			
	// Build the landmark's mask, updating its size and window
	maxSize = 0;
	for (int j=0; j<numActiveRegions; j++)
	{
                reg_id = mRetinalCenter->getActiveRegion(j);
                region = mRetinalCenter->getRegion(reg_id);

                overlap = maty::Area::getWindowOverlap(roi_window, &region->window);

                // select those regions that lay inside the roi's window (or partially inside)
                if (overlap > joinObjectFraction)
                {
                    // add region to selected group
                    mVisualCenter->addFormingRegion(reg_id);

                    // update landmark's size
                    oLandmark->increaseArea(region->pixels);

                    // update landmark's window
                    if (j == 0)
                        oLandmark->setWindow (&region->window);
                    else
                        oLandmark->addWindow (&region->window);

                    // update landmark's mask
                    oLandmark->addMask(region->mask, &region->window);

                    // update landmark's color (with color of its biggest region)
                    if (region->pixels > maxSize)
                    {
                        oLandmark->setColor(region->color);

                        maxSize = region->pixels;
                    }
                }
	}		
	 
#ifdef DEBUG_MODE
	cout << " end - formObject" << endl;
#endif
}  
}




