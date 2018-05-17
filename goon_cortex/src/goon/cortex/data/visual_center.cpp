/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


#include "goon/cortex/data/visual_center.h"


namespace goon
{
VisualCenter::VisualCenter (CvSize image_size)
{	
    storage = cvCreateMemStorage(0);

    pthread_mutex_init (&mutex, NULL);
    oLandmarkV1 = new Landmark (image_size.width, image_size.height);
    oLandmarkV2 = new Landmark (image_size.width, image_size.height);
    oLandmarkT = new Landmark (image_size.width, image_size.height);
    bnewV1 = false;

    imageArea = image_size.width * image_size.height;

    seq_context = cvCreateSeq (CV_SEQ_ELTYPE_GENERIC, sizeof(CvSeq), sizeof(st_context), storage);
    seq_forming_regions = cvCreateSeq(CV_32SC1, sizeof(CvSeq),sizeof(int), storage);
}


VisualCenter:: ~VisualCenter ()
{
    // release memory storage
    cvReleaseMemStorage (&storage);

    if (oLandmarkV1 != NULL)
        delete oLandmarkV1;
    if (oLandmarkV2 != NULL)
        delete oLandmarkV2;
    if (oLandmarkT != NULL)
        delete oLandmarkT;
    pthread_mutex_destroy (&mutex);
}


// Acces dynamic landmark version
Landmark* VisualCenter::getLandmarkV1 () {return oLandmarkV1;}

// Acces stable landmark version
Landmark* VisualCenter::getLandmarkV2 () {return oLandmarkV2;}

CvSeq* VisualCenter::getLandmarkContext () {return seq_context;}

void VisualCenter::clearLandmarkContext ()
{
	cvClearSeq (seq_context);
}

// Access the landmark's global position
int* VisualCenter::getLandmarkPosition () {return global_position;}
// Set the landmark's global position
void VisualCenter::setLandmarkPosition (int absolute_pan, int absolute_tilt)
{
    	global_position[0] = absolute_pan;
	global_position[1] = absolute_tilt;
}

int VisualCenter::getLandmarkID () {return ID;}
void VisualCenter::setLandmarkID (int id) {ID = id;}


// clone landmark V1 to transfer version (mutex protected)
// IMPORTANTE: comprobar que la clonacion se puede hacer así
void VisualCenter::transferV1()
{
    pthread_mutex_lock (&mutex);
    delete (oLandmarkT);
    oLandmarkT = new Landmark(*oLandmarkV1);
    bnewV1 = true;  // raise new version flag
    pthread_mutex_unlock (&mutex);
}

// clone transfer version to landmark V2 (mutex protected)
// IMPORTANTE: comprobar que la clonacion se puede hacer así
void VisualCenter::transferV2()
{
    pthread_mutex_lock (&mutex);
    delete (oLandmarkV2);
    oLandmarkV2 = new Landmark(*oLandmarkT);
    bnewV1 = false; // clear new version flag
    pthread_mutex_unlock (&mutex);
}

// Checks if there's a new V1 version available
bool VisualCenter::isV1Updated()
{
    bool bupdated;
    pthread_mutex_lock (&mutex);
    bupdated = bnewV1;
    pthread_mutex_unlock (&mutex);
    return (bupdated);
}

int VisualCenter::getImageArea()  {return imageArea;}

CvSeq* VisualCenter::getListFormingRegions () {return seq_forming_regions;}

 void VisualCenter::addFormingRegion (int reg_id)
{
    cvSeqPush (seq_forming_regions, &reg_id);
}


void VisualCenter::removeFormingRegion (int pos)
{
	cvSeqRemove (seq_forming_regions, pos);
}


// Return the Id of the retinal region in the specified position of the selected regions list
int VisualCenter::getFormingRegion (int pos)
{
    return (*(int*)cvGetSeqElem (seq_forming_regions, pos));
}


void VisualCenter::popFormingRegion (int* preg_id)
{
    cvSeqPopFront (seq_forming_regions, preg_id);
}


int VisualCenter::getNumFormingRegions ()
{
    return (seq_forming_regions->total);
}


void VisualCenter::clearListFormingRegions ()
{
	cvClearSeq (seq_forming_regions);
}

}