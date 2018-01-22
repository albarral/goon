#ifndef __GOON_CORTEX_VISUAL_CENTER_H
#define __GOON_CORTEX_VISUAL_CENTER_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <pthread.h>

#include <opencv2/core/core.hpp>
#include "goon/cortex/data/Landmark.h"

namespace goon
{
class VisualCenter
{
    private:
        pthread_mutex_t mutex;
        Landmark* oLandmarkV1;       // landmark version 1 (attention thread)
        Landmark* oLandmarkV2;       // landmark version 2 (goon vision thread)
        Landmark* oLandmarkT;         // landmark transfer version (shared by both threads)
        bool bnewV1;                        // marks a new available V1 version
        CvSeq* seq_context;             // contextual data
	int global_position[2];
        int ID;                                 // landmark ID
        int imageArea;
        CvSeq* seq_forming_regions;     // selected group of retinal regions that form the Selected
        CvMemStorage* storage;

public:

        VisualCenter(CvSize image_size);
        ~VisualCenter();

        // Acces dynamic landmark version
        Landmark* getLandmarkV1 ();
        // Acces stable landmark version
        Landmark* getLandmarkV2 ();
        
        CvSeq* getLandmarkContext ();
        void clearLandmarkContext ();

        int* getLandmarkPosition ();
        void setLandmarkPosition (int absolute_pan, int absolute_tilt);

        int getLandmarkID ();
        void setLandmarkID (int id);

        // clone landmark version 1 to transfer version (mutex protected)
        void transferV1();
        // clone transfer version to landmark version 2 (mutex protected)
        void transferV2();

        // Return the value of the new version flag
        bool isV1Updated();

        int getImageArea();

        // funcions for seq_forming_regions
        CvSeq* getListFormingRegions ();
        void addFormingRegion (int reg_id);
        void removeFormingRegion (int pos);
        int getFormingRegion (int pos);
        void popFormingRegion (int* preg_id);
        int getNumFormingRegions ();
        void clearListFormingRegions ();

};
   
}  
#endif
