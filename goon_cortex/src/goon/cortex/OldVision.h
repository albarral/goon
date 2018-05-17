#ifndef __GOON_CORTEX_OLDVISION_H
#define __GOON_CORTEX_OLDVISION_H

/***************************************************************************
 *   Copyright (C) 2012 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/core/core.hpp>
#include <log4cxx/logger.h>
#include <pthread.h>

#include "camera/goon_camera.h"

#include "goon/cortex/data/retinal_center.h"
#include "goon/cortex/data/visual_center.h"
#include "goon/cortex/data/memory_center.h"
#include "modules/attention/attention.h"
#include "goon/cortex/recognition/recognition.h"
#include "visualization/visualization.h"

namespace goon
{
class OldVision
{
    private:
        static log4cxx::LoggerPtr logger;
        RetinalCenter *oRetinalCenter;
        VisualCenter *oVisualCenter;
        MemoryCenter *oMemoryCenter;
        Recognition* oRecognition;
	int date;
	CvSeq* seq_recent_objects;
	float Kvisual_field;
	int center_x;
	int center_y;
        CvMemStorage* vision_storage;
        pthread_t attentionThread;

    public:
        OldVision(Heart* oHeart, goonCamera* oGoonCamera);
        ~OldVision();

        void start();
        void stop();

        void setVisionParameters (int same_RGB, int similar_RGB, int retinal_samples);
        // This function changes main parameters of the vision system.

        bool findNewLandmark ();
        // This function finds a new landmark in the visual field by forcing an attention shift.
        // If a landmark is found the function returns true, otherwise false is returned.

        bool isLandmarkFocused ();
        // This function checks if a visual landmark is currently focused.

        bool identifyObject (int *object_id);
        // This function implements the object recognition process if a new detected landmark is available.
        // It identifies the landmark among the models stored in memory and updates it with a new or updated object's model.
        // It returns true if the process could be done, or false otherwise.

        void getLandmarkMask (IplImage* mask_object);
        // This function returns a copy of the landmark's mask.

        void getLandmarkFeatures (float* hsv_color, float* scale, float* shape_factor, int* orientation);
        // This function returns the landmark's main features (color, scale, shape, orientation).

        void getLandmarkWindow (int* pos, int* sides);
        // This function returns the landmark's enclosing window.

        void getLandmarkRelPosition (float* rel_pan, float* rel_tilt);
        // This function returns the landmark's relative position (in pan-tilt value).

        void getRelativePanTilt (int *visual_point, float* rel_pan, float* rel_tilt);
        // This function computes the relative pan and tilt values of the specified visual point.

        void setVisionShowing (bool bshow);
        // This function enables/disables the vision to show its output.

        void showVisionOutput (IplImage* image_show);
        // This function shows the vision output in the specified image.

        void showVisionTarget (IplImage* image_show);
        // This function shows the contour of the visual target in the specified image.

        void setLandmarkGlobPosition (int head_pan, int head_tilt);
        // This function sets the landmark's global position (necessary for later contextual recognition)

    private:
        void updateVisualContext (int object_id);
        // This function adds a new object to the list of recent objects, unless the given object is already in the list.
};
    
void* runAttention (void* arg);
}
#endif
