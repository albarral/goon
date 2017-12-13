#ifndef __GOON_RETINAL_HSV_ESSENCE_H
#define __GOON_RETINAL_HSV_ESSENCE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cstring>              // for debug purpose
#include "opencv2/core/core.hpp"

//#define __ADAPTIVE_ESSENCE_H

// THIS CLASS IS IN RESEARCH STAGE !!! 

namespace goon
{
// This class computes the HSV color essence of a given region, classifing it as dark, grey or colored.
// HOW: It does so by analyzing the region's mean color in HSV space.
// IMPORTANT: It compares hsv colors against the hsv essence using different discriminances depending on the classified type:
// colored: strict hue, but permisive saturation & value.
// grey: strict saturation, but permisive value (hue is ignored).
// dark: strict value (hue & saturation are ignored).
// DRAWBACKS: sharp changes on the type classification produce undesired discontinuities in color comparisons. 
// ON RESEARCH: An adaptive version is being pursued where color discriminances are not fixed constants, but variable and dependent on each region.
class HSVEssence
{
public:
        
    // Types of color essence    
    enum eType
    {
        eTYP_UNDEFINED,
        eTYP_COLOR,
        eTYP_GREY,
        eTYP_DARK,
    };

private:
    int type;
    cv::Vec3f hsv_main;    // hsv   
    cv::Vec3f hsv_dev;    // hsv   
    int VAL_DARK;
    int SAT_GREY;
    float HUE_DISC;
    float SAT_DISC;
    float VAL_DISC;
    float SAT_DISC_GREY;
    float VAL_DISC_DARK;
    // debug
    int num_updates;
    bool bchanged;          // indicates whether the type has changed
    
#ifdef __ADAPTIVE_ESSENCE_H    
    // adaptive version
    int VAL_DARK2;
    int SAT_GREY2;
    float hue_disc;
    float sat_disc;
    float val_disc;
    float k;
    float min_hue_disc;
    float min_sat_disc;
    float min_val_disc;
    float Kdark;
    float Kgrey;
#endif
    
public:

    HSVEssence();
    ~HSVEssence();

    int getType() {return type;};
    cv::Vec3f& getMainColor () {return hsv_main;}
    cv::Vec3f& getColorDev () {return hsv_dev;}
    
    // resets the essence values
    void reset();
    
    // sets the main hsv from an rgb value
    void setMainFromRGB (cv::Vec3f& rgb_color);    

    // computes the hsv deviation of the given rgb grid (using the specified window and mask)
    void computeDeviationFromRGB (cv::Mat& grid_rgb, cv::Rect& window, cv::Mat& grid_mask);    
    
    // compares the given hsv color to the essence value
    float compare (cv::Vec3i& hsv_color);
    // adaptive color version
    //float compare2 (cv::Vec3i& hsv_color);
    
    int getNumUpdates() {return num_updates;};        
    bool typeChanged() {return bchanged;};
    // returns a string indicating the essence type
    std::string getName ();
};
}  
		  	    		  
  
#endif
