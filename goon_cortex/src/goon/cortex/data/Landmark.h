#ifndef __GOON_CORTEX_LANDMARK_H
#define __GOON_CORTEX_LANDMARK_H

/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <opencv2/core/core.hpp>
#include "landmarks.h"			

namespace goon
{
class Landmark
{
    private:
        cv::Mat mask;	
        cv::Rect window;	
        int area;   // in pixels
        float scale;
        float color[3];             // hsv
	float shape_factor;
	int orientation;
	int centroid[2];
	int num_regions;
	st_lmk_region lmk_regions[REGIONS_PER_LMK];
        CvMemStorage* storage;

public:

        Landmark(int w, int h);
        ~Landmark();

        cv::Mat& getMask() {return mask;};
        void clearMask();
        void addMask(cv::Mat& amask, cv::Rect& awindow);

        cv::Rect& getWindow() {return window;};
        void setWindow(cv::Rect& awindow);
        void addWindow(cv::Rect& awindow);

        int getArea() {return area;};
        void setArea(int value) {area = value;};
        void increaseArea (int value);

        float getScale() {return scale;};
        void setScale(float value) {scale = value;};

        float* getColor() {return color;};
        void setColor(float *value);

        float getShapeFactor() {return shape_factor;};
        void setShapeFactor(float value) {shape_factor = value;};

        int getOrientation() {return orientation;};
        void setOrientation (int value) {orientation = value;};

        int* getCentroid() {return centroid;};
        void setCentroid (int* value);

        int getNumRegions() {return num_regions;};
        void setNumRegions(int value) {num_regions = value;};

        st_lmk_region* getRegions ();
        st_lmk_region* getRegion (int i);

        void setNumLmkRegions (int num); // deprecated

        // Clears the regions of the landmark.
        void clearRegions ();

};
} 
  
#endif
