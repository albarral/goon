#ifndef __GOON_CORTEX_CHARACTERIZATION_H
#define __GOON_CORTEX_CHARACTERIZATION_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <log4cxx/logger.h>
#include "goon/cortex/data/retinal_center.h"
#include "goon/cortex/data/visual_center.h"
#include "goon/cortex/data/landmarks.h"


namespace goon
{
class Characterization
{
private:
    static log4cxx::LoggerPtr logger;
    RetinalCenter* mRetinalCenter;
    VisualCenter* mVisualCenter;
    Landmark* oLandmark;

public:
    Characterization (RetinalCenter* oRetinalCenter, VisualCenter* oVisualCenter);
    ~Characterization();

     void checkGlobalObject ();
    // This function computes the landmark's shape, centroid, scale and orientation.

    bool checkObjectDetails ();
    // This function builds the internal structure of the landmark based in its composing regions.
    // The smaller regions are rejected and only the relevant ones are characterized, using color, shape and context information.
    // The function returns true if the structure could be built, or false otherwise.

    // This function fixes the characterized landmark version in the visual center. 
    void fixLandmark ();

private:

  void filterRetinalRegions (int min_size);
  // This function checks the list of focused retinal regions selecting the most relevant ones for the landmark's characterization.
  // It also sorts them by size in decreasing order.

  void characterizeRegions ();
  // This function characterizes each landmark region with color, shape and context information.

  void characterizeNeighbours (int base_region);
    // This function characterizes the neighbourhood of a base region in 2 different modes:
    // if base region is simple or collection -> no subregion neighbours are considered
    // if base region is subregion -> only subregion neighbours are considered

  bool checkSubregionRelation (st_lmk_region* lmk_region1, st_lmk_region* lmk_region2);
    // This function checks if any of the input regions is subregion of the other. It returns true if the regions are related, or false otherwise.

  void setNeighbourData (st_lmk_region* lmk_region1, int n, st_lmk_region* lmk_region2, int list_position);

  void showLandmarkFeatures ();

  void showRegionFeatures (st_lmk_region* lmk_region, int num);
 };
}
#endif
