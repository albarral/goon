/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "goon/cortex/OldVision.h"
#include "goon/cortex/config/vision_defines.h"

using namespace log4cxx;

namespace goon
{
LoggerPtr OldVision::logger(Logger::getLogger("goon.cortex.OldVision"));

// Constructor
OldVision::OldVision (Heart* oHeart, goonCamera* oGoonCamera)
{
    CvSize image_size;
    int visual_field;

    vision_storage = cvCreateMemStorage(0);

    date = 0;
    seq_recent_objects = cvCreateSeq(CV_32SC1, sizeof(CvSeq),sizeof(int), vision_storage);

    oGoonCamera->getCaptureSize(&image_size.width, &image_size.height);
    visual_field = oGoonCamera->getVisualField();

    Kvisual_field = (float)visual_field / image_size.width;
    center_x = image_size.width / 2;
    center_y = image_size.height / 2;

    oRetinalCenter = new RetinalCenter (image_size);
    oVisualCenter = new VisualCenter (image_size);
    oMemoryCenter = new MemoryCenter ();

    oVisualization = new Visualization(image_size);
    oVisualization->setShowFlags(true, true, true);

    oAttention = new Attention (oHeart, oGoonCamera, oRetinalCenter, oVisualCenter, oVisualization);
    oRecognition = new Recognition (oVisualCenter, oMemoryCenter, image_size.width, image_size.height);    
}


// Destructor
OldVision::~OldVision ()
{
    cvReleaseMemStorage (&vision_storage);

    if (oRetinalCenter != NULL)
        delete (oRetinalCenter);
    if (oVisualCenter != NULL)
        delete (oVisualCenter);
    if (oMemoryCenter != NULL)
        delete (oMemoryCenter);

    if (oVisualization != NULL)
        delete (oVisualization);

    if (oAttention != NULL)
        delete (oAttention);
    if (oRecognition != NULL)
        delete (oRecognition);
}



void OldVision::start ()
{
#ifdef DEBUG_MODE
	cout << " init - start" << endl;
#endif
        int ret;
				
    LOG4CXX_INFO(logger, "starting VISION ... ");

    // launch fast vision thread
    ret = pthread_create (&attentionThread, NULL, runAttention, oAttention);
    if (ret > 0)
    {
        LOG4CXX_FATAL(logger, "Error creating attention thread ... ");
        exit (1);
    }

#ifdef DEBUG_MODE
	cout << " end - start" << endl;
#endif
}



void OldVision::stop()
{
#ifdef DEBUG_MODE
	cout << " init - stop" << endl;
#endif

    LOG4CXX_INFO(logger, "ending VISION ...");

    oAttention->stop();

    pthread_join (attentionThread, NULL);
			
#ifdef DEBUG_MODE
	cout << " end - stop" << endl;
#endif
}



// This function changes main parameters of the vision system.
void OldVision::setVisionParameters (int same_RGB, int similar_RGB, int retinal_samples)
{
#ifdef DEBUG_MODE
	cout << " init - setVisionParameters" << endl;
#endif

        LOG4CXX_INFO(logger, "new vision parameters");

	oAttention->changeRetinalVision(retinal_samples, same_RGB, similar_RGB);
	oAttention->changePeripheralVision(same_RGB, similar_RGB);
	
#ifdef DEBUG_MODE
	cout << " end - setVisionParameters" << endl;
#endif
}


// This function finds a new landmark in the visual field by forcing an attention shift.
// If a landmark is found the function returns true, otherwise false is returned.
bool OldVision::findNewLandmark ()
{		
    int last_counter, counter;

    oAttention->shift();

    oAttention->getCounter(&counter);
    last_counter = counter;

    while (counter < last_counter+2)
    {
        oAttention->getCounter(&counter);
        usleep (50000);
    }

    return (oAttention->isFocused());
}



// This function checks if a visual landmark is currently focused.
bool OldVision::isLandmarkFocused ()
{		
    return (oAttention->isFocused());
}


// This function implements the object recognition process if a new detected landmark is available.
// It identifies the landmark among the models stored in memory and updates it with a new or updated object's model.
// It returns true if the process could be done, or false otherwise.
bool OldVision::identifyObject (int *object_id)
{
#ifdef DEBUG_MODE
	cout << " init - identifyObject" << endl;
#endif
	bool bnewUpdate, bnew_view, bmatched;
	int matched_object,	new_object;
	
    date++;

    LOG4CXX_DEBUG(logger, "recognition init - " << date);

    bnewUpdate = oVisualCenter->isV1Updated();

    if (bnewUpdate)
    {
        oVisualCenter->transferV2();

        bmatched = oRecognition->recogniseObject (seq_recent_objects, &matched_object);

        if (bmatched)
        {
            bnew_view = !(oRecognition->isModelGood());

            oMemoryCenter->updateObject (oVisualCenter, matched_object, bnew_view, date);

            updateVisualContext (matched_object);

            *object_id = matched_object;
        }
        else
        {
            new_object = oMemoryCenter->createObject (oVisualCenter, date);

            updateVisualContext (new_object);

            *object_id = new_object;
        }
    }

    LOG4CXX_DEBUG(logger, "recognition end");
	
#ifdef DEBUG_MODE
	cout << " end - identifyObject" << endl;
#endif	
	return (bnewUpdate);
}



// This function returns a copy of the landmark's mask.
void OldVision::getLandmarkMask (IplImage* mask_object)
{
#ifdef DEBUG_MODE
	cout << " init - getLandmarkMask" << endl;
#endif
        cvCopy (oVisualCenter->getLandmarkV2()->getMask(), mask_object);

#ifdef DEBUG_MODE
	cout << " end - getLandmarkMask" << endl;
#endif
}  



// This function returns the landmark's main features (color, area, shape, orientation).
void OldVision::getLandmarkFeatures (float* hsv_color, float* scale, float* shape_factor, int* orientation)
{
#ifdef DEBUG_MODE
	cout << " init - getLandmarkFeatures" << endl;
#endif
        float* lmkColor;

        Landmark* oLandmark = oVisualCenter->getLandmarkV2();

	lmkColor = oLandmark->getColor();

	for (int i=0; i<3; i++)
		hsv_color[i] = lmkColor[i];

	*scale = oLandmark->getScale();
	*shape_factor = oLandmark->getShapeFactor();
	*orientation = oLandmark->getOrientation();
	
#ifdef DEBUG_MODE
	cout << " end - getLandmarkFeatures" << endl;
#endif
}  



// This function returns the landmark's enclosing window.
void OldVision::getLandmarkWindow (int* pos, int* sides)
{		
#ifdef DEBUG_MODE
	cout << " init - getLandmarkWindow" << endl;
#endif						
        CvRect* lmkWindow = oVisualCenter->getLandmarkV2()->getWindow();
	
	pos[0] = lmkWindow->x;
	pos[1] = lmkWindow->y;
	sides[0] = lmkWindow->width;
	sides[1] = lmkWindow->height;
	
#ifdef DEBUG_MODE
	cout << " end - getLandmarkWindow" << endl;
#endif
}



// This function returns the landmark's relative position (in pan-tilt value).
void OldVision::getLandmarkRelPosition (float* rel_pan, float* rel_tilt)
{		
#ifdef DEBUG_MODE
	cout << " init - getLandmarkPosition" << endl;
#endif							
	// getRelativePanTilt ()
	getRelativePanTilt (oVisualCenter->getLandmarkV2()->getCentroid(), rel_pan, rel_tilt);
			
#ifdef DEBUG_MODE
	cout << " end - getLandmarkPosition" << endl;
#endif
}



// This function computes the relative pan and tilt values of the specified visual point.
void OldVision::getRelativePanTilt (int *visual_point, float* rel_pan, float* rel_tilt)
{		
#ifdef DEBUG_MODE
	cout << " init - getRelativePanTilt" << endl;
#endif
	
	*rel_pan = (visual_point[0] - center_x) * Kvisual_field;
	*rel_tilt = (center_y - visual_point[1]) * Kvisual_field;	// image y axis looks down
	
#ifdef DEBUG_MODE
	cout << " end - getRelativePanTilt" << endl;
#endif
}



// This function enables/disables the vision to show its output.
void OldVision::setVisionShowing (bool bshow)
{
	oAttention->show(bshow);
}



// This function shows the vision output in the specified image.
void OldVision::showVisionOutput (IplImage* image_show)
{
#ifdef DEBUG_MODE
	cout << " init - showVisionOutput" << endl;
#endif

        oVisualization->drawOutputs();

        oVisualization->getPeripheralImage(image_show);

#ifdef DEBUG_MODE
	cout << " end - showVisionOutput" << endl;
#endif
}



// This function shows the contour of the visual target in the specified image.
void OldVision::showVisionTarget (IplImage* image_show)
{
    if (oAttention->isFocused())
    {
        oVisualization->drawOutputs();

        oVisualization->getObjectImage(image_show);
    }
    else
        cvCopy (oVisualization->getCenter()->getImageAttended(), image_show);
}


// This function sets the landmark's global position (necessary for later contextual recognition)
void OldVision::setLandmarkGlobPosition (int head_pan, int head_tilt)
{
#ifdef DEBUG_MODE
	cout << " init - setLandmarkPosition" << endl;
#endif
	int pos[2];
        float rel_pan, rel_tilt;

        Landmark* oLandmark = oVisualCenter->getLandmarkV2();
        CvRect* lmkWindow = oLandmark->getWindow();

	pos[0] = lmkWindow->x + 0.5*lmkWindow->width;
	pos[1] = lmkWindow->y + 0.5*lmkWindow->height;

        getRelativePanTilt (pos, &rel_pan, &rel_tilt);

        oVisualCenter->setLandmarkPosition (head_pan + rel_pan, head_tilt + rel_tilt);

#ifdef DEBUG_MODE
	cout << " end - setLandmarkPosition" << endl;
#endif
}


// This function adds a new object to the list of recent objects, unless the given object is already in the list.
void OldVision::updateVisualContext (int object_id)
{
#ifdef DEBUG_MODE
	cout << " init - updateVisualContext" << endl;
#endif
	bool bfound = false; 
	int last_pos, last_object, oldest_object;
				
	// check if the object is already in the list
	if (seq_recent_objects->total > 0)
	{
		last_pos = seq_recent_objects->total - 1;
		last_object = *(int*)cvGetSeqElem (seq_recent_objects, last_pos);						  
		bfound = (object_id == last_object);
	}
	// if not found, add the new object to the list and remove the oldest one if the list grows too much.
	if (!bfound)
	{
		cvSeqPush (seq_recent_objects, &object_id);
		 			  
		if (seq_recent_objects->total > RECENT_MEMORY)
			cvSeqPopFront (seq_recent_objects, &oldest_object);		
	}	

#ifdef DEBUG_MODE
	cout << " end - updateVisualContext" << endl;
#endif
}  
}

// Thread funcion that runs the Attention module
void* runAttention (void* arg)
{
    //LOG4CXX_INFO(logger, "Attention thread - started");

    Attention* pAttention = (Attention*) arg;

    pAttention->run();

    //LOG4CXX_INFO(logger, "Attention thread - ended");
}




