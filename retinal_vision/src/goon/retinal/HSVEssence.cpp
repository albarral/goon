/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>
#include "opencv2/imgproc/imgproc.hpp"          // for cvtColor

#include "goon/retinal/HSVEssence.h"
#include "goon/features/color/rgb_color.h"

namespace goon
{
// constructor
HSVEssence::HSVEssence ()
{        
    // grey and dark thresholds
    SAT_GREY = 255*0.20;
    VAL_DARK = 255*0.20;
    // color discriminances
    HUE_DISC = 10.0;
    SAT_DISC = 255*0.30;
    VAL_DISC = 255*0.30;
    SAT_DISC_GREY = 255*0.10;
    VAL_DISC_DARK = 255*0.10;

    reset();    

    #ifdef __ADAPTIVE_ESSENCE_H        
    SAT_GREY2 = 255*0.50;
    VAL_DARK2 = 255*0.50;
    min_hue_disc = 5;
    min_sat_disc = 0.10*255;
    min_val_disc = 0.10*255;
    k = 2;
    hue_disc = min_hue_disc;
    sat_disc = min_sat_disc;
    val_disc = min_val_disc;
    #endif
}

// destructor
HSVEssence::~HSVEssence()
{
}


void HSVEssence::reset()
{
    type = eTYP_UNDEFINED;
    bchanged = false;
    num_updates = 0;
}


void HSVEssence::setMainFromRGB(cv::Vec3f& rgb_color)
{
    int last_type = type;
    
    // compute main hsv
    RGBColor::toHSV(rgb_color, hsv_main);
    
    // low value -> dark essence
    if (hsv_main[2] < VAL_DARK)
        type = eTYP_DARK;
    // low saturation -> grey essence
    else if (hsv_main[1] < SAT_GREY)
        type = eTYP_GREY;
    // else -> color essence
    else
        type = eTYP_COLOR;      
    
    num_updates++;

    bchanged = (type != last_type);
    
    #ifdef __ADAPTIVE_ESSENCE_H    
    Kdark = 1.67 - (hsv_main[2] / (0.30*255));
    Kgrey = 1.67 - (hsv_main[1] / (0.30*255));
    if (Kdark > 1.0)
        Kdark = 1.0;
    else if (Kdark < 0)
        Kdark = 0.0;
    if (Kgrey > 1.0)
        Kgrey = 1.0;
    else if (Kgrey < 0)
        Kgrey = 0.0;
    #endif    
}


void HSVEssence::computeDeviationFromRGB(cv::Mat& grid_rgb, cv::Rect& window, cv::Mat& grid_mask)
{
    // get grid's roi
    cv::Mat grid_roi = grid_rgb(window);
    cv::Mat grid_scaled, grid_hsv;        

    // Convert RGB to HSV:
    // This conversion expects [0,1] ranges when input image is 32F (delivering sat and value also in this range).
    // As grid_rgb is a 32F image we must scale it down to the [0,1] range.
    if (grid_rgb.depth() == CV_32F)
        grid_scaled = grid_roi * (1./255);
    else 
        return;    
    
    cv::cvtColor(grid_scaled, grid_hsv, CV_RGB2HSV);
    
    // separate channels (32F images)
    cv::Mat grid_hue, grid_sat, grid_val;    
    cv::Mat HSV_channels[3];    
    split(grid_hsv, HSV_channels);
    grid_hue = HSV_channels[0];
    grid_sat = HSV_channels[1];
    grid_val = HSV_channels[2];

   // ... compute deviations    
    cv::Mat mat_dev;
    // sat
    mat_dev = grid_sat * 255.0;
    mat_dev = mat_dev - hsv_main[1];
    mat_dev = abs(mat_dev);
    cv::Scalar sat_dev = mean(mat_dev, grid_mask);

    // value
    mat_dev = grid_val * 255.0;
    mat_dev = mat_dev - hsv_main[2];
    mat_dev = abs(mat_dev);
    cv::Scalar val_dev = mean(mat_dev, grid_mask);

    // hue
    mat_dev = abs(grid_hue - hsv_main[0]);
    // correct differences > 180 -> (absdif > 180) absdif = 360 - absdif
    cv::Mat mask_wrong = mat_dev > 180;
    cv::Mat mat_correction = 360 - mat_dev;
    mat_correction.copyTo(mat_dev, mask_wrong);
    cv::Scalar hue_dev = mean(mat_dev, grid_mask);   
    
    hsv_dev[0] = hue_dev(0);
    hsv_dev[1] = sat_dev(0);
    hsv_dev[2] = val_dev(0);

    #ifdef __ADAPTIVE_ESSENCE_H    
    // compute hsv discriminances      
    hue_disc = std::round(k*hsv_dev[0]);
    sat_disc = std::round(k*hsv_dev[1]);
    val_disc = std::round(k*hsv_dev[2]);
    
    if (hue_disc < min_hue_disc)
        hue_disc = min_hue_disc;
    if (sat_disc < min_sat_disc)
        sat_disc = min_sat_disc;
    if (val_disc < min_val_disc)
        val_disc = min_val_disc;
    #endif
}


float HSVEssence::compare(cv::Vec3i& hsv_color)
{
    float dist, dist1, dist2, dist3;
        
    switch (type)
    {
        case eTYP_COLOR:
            // maximum of the 3 distances
            dist1 = std::fabs((float)hsv_color[0] - hsv_main[0]);
            if (dist1 > 180)
                dist1 = 360 - dist1;
            dist1 = dist1 / HUE_DISC;
            dist2 = std::fabs((float)hsv_color[1] - hsv_main[1]) / SAT_DISC;
            dist3 = std::fabs((float)hsv_color[2] - hsv_main[2]) / VAL_DISC;
            dist = (dist1 > dist2 ? dist1 : dist2);
            if (dist3 > dist)
                dist = dist3;
            break;
            
        case eTYP_GREY:
            // maximum of the 2 distances
            dist2 = std::fabs((float)hsv_color[1] - hsv_main[1]) / SAT_DISC_GREY;
            dist3 = std::fabs((float)hsv_color[2] - hsv_main[2]) / VAL_DISC;
            dist = (dist2 > dist3 ? dist2 : dist3);
            break;
        
        case eTYP_DARK:
            dist = std::fabs((float)hsv_color[2] - hsv_main[2]) / VAL_DISC_DARK;
            break;
            
        default:
            dist = 0;
            break;
    }
    
    return dist;    
}


#ifdef __ADAPTIVE_ESSENCE_H    
float HSVEssence::compare2(cv::Vec3i& hsv_color)
{
    float dist, dist1, dist2, dist3;
                    
    if (type == eTYP_UNDEFINED)
    {
        dist = 0;
    }
    else
    {
        // maximum of the 3 distances
        dist1 = std::fabs((float)hsv_color[0] - hsv_main[0]);
        if (dist1 > 180)
            dist1 = 360 - dist1;
//        dist1 = (1.0 - Kdark)*(1.0 - Kgrey)*dist1 / hue_disc;
//        dist2 = std::fabs((float)hsv_color[1] - hsv_main[1])*(1.0 - Kdark) / sat_disc;
        dist1 = dist1 / hue_disc;
        dist2 = std::fabs((float)hsv_color[1] - hsv_main[1]) / sat_disc;
        dist3 = std::fabs((float)hsv_color[2] - hsv_main[2]) / val_disc;
        dist = (dist1 > dist2 ? dist1 : dist2);
        if (dist3 > dist)
            dist = dist3;
    }
    
    return dist;    
}
#endif


std::string HSVEssence::getName()
{
    switch (type)
    {
        case eTYP_UNDEFINED:
            return "undefined";                     
            break;

        case eTYP_COLOR:
            return "color";                     
            break;

        case eTYP_GREY:
            return "grey";                     
            break;

        case eTYP_DARK:
            return "dark";                     
            break;
            
        default:
            return "invalid";
            break;
    }                            
}

}
