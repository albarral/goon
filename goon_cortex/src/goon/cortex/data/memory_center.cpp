/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "memory_center.h"
	
using namespace log4cxx;
namespace goon
{
LoggerPtr MemoryCenter::logger(Logger::getLogger("goon.cortex.memorycenter"));

MemoryCenter::MemoryCenter ()
{
#ifdef DEBUG_MODE
	cout << " init - InitMemoryCenter" << endl;
#endif	 		
	memory_storage = cvCreateMemStorage(0);
	
	// init object views
	for (int i=0; i<MAX_OBJECTS; i++)
	{
		objects[i].seq_model_views = cvCreateSeq (CV_32SC1, sizeof(CvSeq),sizeof(int), memory_storage);
		objects[i].seq_context = cvCreateSeq (CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_context), memory_storage);	
	}
	
	// init model regions
	for (int i=0; i<MAX_MODEL_REGIONS; i++)
	{
		model_regions[i].seq_subregions = cvCreateSeq(CV_32SC1, sizeof(CvSeq),sizeof(int), memory_storage);
	}

	num_objects = num_models = num_regions = 0; 	
				
#ifdef DEBUG_MODE
	cout << " end - InitMemoryCenter" << endl;
#endif	 		
}



MemoryCenter::~MemoryCenter()
{
#ifdef DEBUG_MODE
	cout << " init - EndMemoryCenter" << endl;
#endif	 		
	
	cvReleaseMemStorage (&memory_storage);	
	
#ifdef DEBUG_MODE
	cout << " end - EndMemoryCenter" << endl;
#endif	 		
}


st_object* MemoryCenter::getObject (int i) {return &(objects[i]);}
st_model* MemoryCenter::getModel (int i) {return &(models[i]);}
st_model_region* MemoryCenter::getModelRegion (int i) {return &(model_regions[i]);}

int MemoryCenter::getNumObjects()  {return num_objects;}
int MemoryCenter::getNumModels() {return num_models;}
int MemoryCenter::getNumModelRegions() {return num_regions;}


// This function stores the present landmark in memory as a new object. It returns the new object's ID.
int MemoryCenter::createObject (VisualCenter* oVisualCenter, int date)
{
#ifdef DEBUG_MODE
	cout << " init - createObject" << endl;
#endif
        Landmark* oLandmark = oVisualCenter->getLandmarkV2();

	num_objects++;		// first object is 1
	st_object* new_object = &(objects[num_objects]);

	new_object->ID = num_objects;
	new_object->merged = false;
	new_object->father_id = 0;
	new_object->num_matches = 0;

	storeContext (new_object, oLandmark->getArea(), oVisualCenter->getLandmarkPosition(), oVisualCenter->getLandmarkContext(), date);

	addView (new_object, oLandmark);

#ifdef DEBUG_MODE
	cout << " end - createObject" << endl;
#endif
	return (new_object->ID);
}



// This function updates an existing object with data from the present landmark.
// If new view is requested the function stores the present landmark as a new object's view.
void MemoryCenter::updateObject (VisualCenter* oVisualCenter, int matched_object, bool bnew_view, int date)
{
#ifdef DEBUG_MODE
	cout << " init - UpdateObject" << endl;
#endif
        Landmark* oLandmark = oVisualCenter->getLandmarkV2();

	st_object* object = &(objects[matched_object]);
	object->num_matches++;

	storeContext (object, oLandmark->getArea(), oVisualCenter->getLandmarkPosition(), oVisualCenter->getLandmarkContext(), date);

	if (bnew_view)
            addView (object, oLandmark);

#ifdef DEBUG_MODE
	cout << " end - UpdateObject" << endl;
#endif
}



// This function stores the last object's position, size, date and context.
void MemoryCenter::storeContext (st_object* object, int lmkPixels, int* lmkPosition, CvSeq* seqlmkContext, int date)
{
#ifdef DEBUG_MODE
	cout << " init - storeContext" << endl;
#endif
	st_context *context;

	object->last_date = date;
	object->last_size = lmkPixels;
	object->last_position[0] = lmkPosition[0];
	object->last_position[1] = lmkPosition[1];

	// store the object's context (avoiding references to itself)
	cvClearSeq (object->seq_context);
	for (int i=0; i < seqlmkContext->total; i++)
	{
		context = (st_context*)cvGetSeqElem (seqlmkContext, i);

		if (context->object_ID != object->ID)
			cvSeqPush (object->seq_context, context);
	}

#ifdef DEBUG_MODE
	cout << " end - storeContext" << endl;
#endif
}



// This function stores a landmark as a new model view in the database, and assigns this view to its corresponding scene object.
void MemoryCenter::addView (st_object* object, Landmark* oLandmark)
{
#ifdef DEBUG_MODE
	cout << " init - addView" << endl;
#endif
	num_models++;

	cvSeqPush (object->seq_model_views, &num_models);

	// storeLandmark
	storeLandmark (&(models[num_models]), oLandmark, object->ID, object->seq_model_views->total);

	// insert also its composing regions
	for (int j=0; j < oLandmark->getNumRegions(); j++)
	{
            // storeRegion
            storeRegion (&model_regions[num_regions], oLandmark->getRegion(j));

            num_regions++;
	}

#ifdef DEBUG_MODE
	cout << " end - addView" << endl;
#endif
}



// This function stores a landmark model in the database
void MemoryCenter::storeLandmark (st_model* model, Landmark* oLandmark, int object_ID, int view_ID)
{
#ifdef DEBUG_MODE
	cout << " init - storeLandmark" << endl;
#endif
	int region_counter;
        float *lmkColor = oLandmark->getColor();

	model->object_ID = object_ID;
	model->view_ID = view_ID;
	model->color[0] = lmkColor[0];
	model->color[1] = lmkColor[1];
	model->color[2] = lmkColor[2];
	model->scale = oLandmark->getScale();
	model->num_regions = oLandmark->getNumRegions();
	model->num_subregions = 0; // before landmark->num_subregions;

	// traslation of  model regions pointers
	region_counter = num_regions;
	for (int i=0; i < oLandmark->getNumRegions(); i++)
		model->list_regions[i] = region_counter++;

#ifdef DEBUG_MODE
	cout << " end - storeLandmark" << endl;
#endif
}



// This function stores a region model in the database
void MemoryCenter::storeRegion (st_model_region* model_region, st_lmk_region* lmk_region)
{
#ifdef DEBUG_MODE
	cout << " init - storeRegion" << endl;
#endif
	int buffer[REGIONS_PER_LMK];
	int buffer_length;

	model_region->ID = lmk_region->ID;
	model_region->type = lmk_region->type;
	// if collection -> transfer list of subregions
	if (lmk_region->seq_subregions->total > 0)
	{
		buffer_length = lmk_region->seq_subregions->total;
		cvSeqPopMulti (lmk_region->seq_subregions, buffer, buffer_length);
		cvSeqPushMulti (model_region->seq_subregions, buffer, buffer_length);
	}
	model_region->color[0] = lmk_region->color[0];
	model_region->color[1] = lmk_region->color[1];
	model_region->color[2] = lmk_region->color[2];
	model_region->weight = lmk_region->weight;
	model_region->shape_factor = lmk_region->shape_factor;
	model_region->orientation = lmk_region->orientation;

	// storeNeighbours()
	storeNeighbours (model_region, lmk_region);

#ifdef DEBUG_MODE
	cout << " end - storeRegion" << endl;
#endif
}



// This function stores the descriptors of all the neighbours of a model region
void MemoryCenter::storeNeighbours (st_model_region* model_region, st_lmk_region* lmk_region)
{
#ifdef DEBUG_MODE
	cout << " init - storeNeighbours" << endl;
#endif

	model_region->num_neighbours = lmk_region->num_neighbours;

	for (int i=0; i < lmk_region->num_neighbours; i++)
	{
		model_region->neighbours[i].ID = lmk_region->neighbours[i].ID;

		model_region->neighbours[i].color[0] = lmk_region->neighbours[i].color[0];
		model_region->neighbours[i].color[1] = lmk_region->neighbours[i].color[1];
		model_region->neighbours[i].color[2] = lmk_region->neighbours[i].color[2];

		model_region->neighbours[i].rel_position[0] = lmk_region->neighbours[i].rel_position[0];
		model_region->neighbours[i].rel_position[1] = lmk_region->neighbours[i].rel_position[1];

		model_region->neighbours[i].rel_weight = lmk_region->neighbours[i].rel_weight;

		model_region->neighbours[i].shape_factor = lmk_region->neighbours[i].shape_factor;
		model_region->neighbours[i].orientation = lmk_region->neighbours[i].orientation;
	}

#ifdef DEBUG_MODE
	cout << " end - storeNeighbours" << endl;
#endif
}



// This function displays the database utilization.
void MemoryCenter::showUsed ()
{
        LOG4CXX_INFO(logger, "DATABASE UTILIZATION");
        LOG4CXX_INFO(logger, "Num objects = " << num_objects << " - " << num_objects*100/MAX_OBJECTS << " %");
        LOG4CXX_INFO(logger, "Num models = " << num_models << " - " << num_models*100/MAX_MODELS << " %");
        LOG4CXX_INFO(logger, "Num regions = " << num_regions << " - " << num_regions*100/MAX_MODEL_REGIONS << " %");
}


// View info of database objects
void MemoryCenter::viewDB ()
{
#ifdef DEBUG_MODE
	cout << " init - viewDB" << endl;
#endif
	int total_matches = 0, matched_objects = 0, multiple_view_objects = 0, additional_views = 0;
	st_object* pobject;

	// header
        LOG4CXX_INFO(logger, "DATABASE INFO ...");
	LOG4CXX_INFO(logger, "shown info -> ID: matches - views - last_date");

	for (int i=1; i <= num_objects; i++)
	{
		pobject = &(objects[i]);

                LOG4CXX_INFO(logger, i << ": " << pobject->num_matches << " - " << pobject->seq_model_views->total << " - " << pobject->last_date);

		if (pobject->num_matches > 0)
		{
                    total_matches += pobject->num_matches;
                    matched_objects ++;

                    if (pobject->seq_model_views->total > 1)
                    {
                            multiple_view_objects ++;
                            additional_views += (pobject->seq_model_views->total-1);
                    }
		}
	}

	// total data
        LOG4CXX_INFO(logger, "total matches = " << total_matches);
	LOG4CXX_INFO(logger, "matched objects = " << matched_objects);
	LOG4CXX_INFO(logger, "multiple view objects = " << multiple_view_objects);
	LOG4CXX_INFO(logger, "additional views = " << additional_views);

#ifdef DEBUG_MODE
	cout << " end - viewDB" << endl;
#endif
}
}

