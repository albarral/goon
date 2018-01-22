#ifndef __GOON_CORTEX_RETINAL_CENTER_H
#define __GOON_CORTEX_RETINAL_CENTER_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/core/core.hpp>
#include "goon/cortex/data/regions.h"

#define MAX_REGIONS 500

namespace goon
{
class RetinalCenter
{
private:
	st_region regions[MAX_REGIONS];
	// IplImage* map_regions;
	CvSeq* seq_active_regions;      // merged regions not included
        CvMemStorage* retinal_storage;

public:
        RetinalCenter(CvSize image_size);
        ~RetinalCenter();

        void initGrids (int grid_rows, int grid_cols);

        void clearRegion (int i);
        // This functions clears the specified region.

        st_region* getRegions ();

        st_region* getRegion (int i);

        // funcions for seq_active_regions
        void addActiveRegion (int reg_id);
        int getActiveRegion (int pos);
        int getNumActiveRegions ();
        void clearListActiveRegions ();
        void sortActiveRegionsBySize ();

        void sortRegionsBySize (CvSeq* seq_regions);

private:
        static int sortBySize (const void* _a, const void* _b, void* userdata);
        // This function sorts regions by size in decreasing order
};

}
#endif
