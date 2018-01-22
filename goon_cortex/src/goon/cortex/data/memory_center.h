#ifndef __GOON_CORTEX_MEMORY_CENTER_H
#define __GOON_CORTEX_MEMORY_CENTER_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <log4cxx/logger.h>
#include "goon/cortex/data/models.h"			
#include "goon/cortex/data/visual_center.h"
						
#define MAX_OBJECTS 	500 			// limit of database objects							
#define MAX_MODELS 	1000 			// 2 models per object
#define MAX_MODEL_REGIONS 10000 	  // 10 regions per model

namespace goon
{
class MemoryCenter
{
    private:        
        static log4cxx::LoggerPtr logger;
	st_object objects[MAX_OBJECTS];
	int num_objects;
	st_model models[MAX_MODELS];
	int num_models;
	st_model_region model_regions[MAX_MODEL_REGIONS];
	int num_regions;
        CvMemStorage* memory_storage;

    public:

        MemoryCenter();
        ~MemoryCenter();

        st_object* getObject (int i);
        st_model* getModel (int i);
        st_model_region* getModelRegion (int i);
        int getNumObjects();
        int getNumModels();
        int getNumModelRegions();

	int createObject (VisualCenter* oVisualCenter, int date);
	// This function stores the present landmark in memory as a new object. It returns the new object's ID.

	void updateObject (VisualCenter* oVisualCenter, int matched_object, bool bnew_view, int date);
	// This function updates an existing object with data from the present landmark.
	// If new view is requested the function stores the present landmark as a new object's view.

    private:

        void storeContext (st_object* object, int lmkPixels, int* lmkPosition, CvSeq* seqlmkContext, int date);
	// This function stores the last object's position, size and date.

	void addView (st_object* object, Landmark* oLandmark);
	// This function stores a landmark as a new model view in the database, and assigns this view to its corresponding scene object.

	void storeLandmark (st_model* model, Landmark* oLandmark, int object_ID, int view_ID);
	// This function stores a landmark model in the database

	void storeRegion (st_model_region* model_region, st_lmk_region* lmk_region);
  	// This function stores a region model in the database

	void storeNeighbours (st_model_region* model_region, st_lmk_region* lmk_region);
	// This function stores the descriptors of all the neighbours of a model region

	void showUsed ();
	// This function displays the database utilization.

	void viewDB ();
	// View info of database objects

};

}
#endif
