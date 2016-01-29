#ifndef __GOON_RETINAL_EXPLORATION_H
#define __GOON_RETINAL_EXPLORATION_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

namespace goon
{
// Support class used for segmentation of images.
// It holds references to various masks and allows efficient exploration of adjacent pixels.
class Exploration
{
public:
    enum ePixelState
    {
        eFREE,
        eEXPLORED,
        eFORBIDEN
    };
    
    enum eLocation
    {
        eEAST,
        eSOUTH,
        eWEST, 
        eNORTH,
        eLOCS_DIM
    };

private:
    cv::Mat mask_explored;         // mask of explored pixels (internal)
    cv::Mat mask_region;            // mask of accepted pixels (internal)
    cv::Mat mask_forbiden;         // mask of forbidden pixels (externally provided)
    cv::Mat image_bgr;               // input image in BGR space (externally provided)
    cv::Mat image_hsv;               // input image in HSV space (externally provided)
    int row_step;                          // real size of image rows      
    cv::Point seed;                       // seed point whose adjacent points are explored
    cv::Point pixel;                        // sensed pixel (adjacent to seed))
    int state;                                // state of the sensed pixel
    uchar *pexplored_seed;           // pointers to seeds  
    uchar *pregion_seed; 
    uchar *pforbiden_seed;
    uchar *pimg_seed;
    uchar *phsv_seed;
    uchar *pexplored_pixel;             // pointers to sensed pixels
    uchar *pregion_pixel; 
    uchar *pforbiden_pixel;
    uchar *pimg_pixel; 
    uchar *phsv_pixel; 
    cv::Rect window;    // explored window
    int xmin;               // explored limits 
    int xmax; 
    int ymin;
    int ymax;
    
public:

    Exploration();
    ~Exploration();

    // Resizes all used masks
    void resize(int img_w, int img_h);
    
    // Provides new inputs and clears the exploration mask
    void prepare(cv::Mat& image_cam, cv::Mat& imageHSV);

    void setForbiddenMask(cv::Mat& mask_segmented);
    
    // Inits the exploration window with the specified point.
    void firstWindow (cv::Point& point);    
    
    // Moves the seed pointers to the specified seed.
    void moveSeed (cv::Point& seed);    
    
    // Explores a location (east, south, west, north) adjacent to the present seed.
    // It returns the pixel state (clean, explored, forbidden).
    int checkAdjacent (int location);
        
    // Updates the pixel state in the present patch location.
    // Marks pixels as accepted or rejected.
    void markPixel (bool baccepted);     
    
    // Obtains the explored window
    void computeWindow();

    // Returns the explored pixel coordinates
    cv::Point& getPixel() {return pixel;};
        
    // Returns the explored pixel RGB color
    void getPixelRGB (cv::Vec3b& rgb_color);        
    // Returns the present seed RGB color
    void getSeedRGB (cv::Vec3b& rgb_color);    
    
    // Returns the explored pixel HSV color
    void getPixelHSV (cv::Vec3i& hsv_color);        
    // Returns the present seed HSV color
    void getSeedHSV (cv::Vec3i& hsv_color);    

    // Returns the explored window.
    cv::Rect& getWindow () {return window;};
    
    cv::Mat& getExploredMask() {return mask_explored;};

    cv::Mat& getRegionMask() {return mask_region;};        
};
		  	    		  
}  
  
#endif
