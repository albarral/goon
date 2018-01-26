/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/retinal/Exploration.h"
#include "goon/data/base/Body.h"

namespace goon
{
// constructor
Exploration::Exploration ()
{
    resize(640, 480);
    window = cv::Rect (0,0,0,0);    
}

// destructor
Exploration::~Exploration()
{
}

void Exploration::resize(int img_w, int img_h)
{
    mask_explored = cv::Mat::zeros(img_h, img_w, CV_8UC1);
    mask_region = cv::Mat::zeros(img_h, img_w, CV_8UC1);

    row_step = mask_explored.step1();
}

// Must be called at the beginning of each exploration process.
void Exploration::prepare(cv::Mat& image_cam, cv::Mat& imageHSV)
{
    cv::Mat mask_roi;
    
    // get new inputs
    image_bgr = image_cam;
    image_hsv = imageHSV;
    
    // reset masks (with roi window)
    if (window.width > 0 && window.height > 0)
    {
         mask_roi = mask_explored(window);
         mask_roi.setTo(0);
         //mask_roi = cv::Scalar(0,0,0);        
         mask_roi = mask_region(window);
         mask_roi.setTo(0);
         //mask_roi = cv::Scalar(0,0,0);        
    }    
}

void Exploration::setForbiddenMask(cv::Mat& mask_segmented)
{
    mask_forbiden = mask_segmented;    
}

void Exploration::firstWindow(cv::Point& point)
{        
    xmin = xmax = point.x;
    ymin = ymax = point.y;    
}


void Exploration::moveSeed (cv::Point& new_seed)    
{
    seed = new_seed;
    
    // move seed pointers to the all necessary masks
    pexplored_seed = mask_explored.ptr(seed.y, seed.x);
    pregion_seed = mask_region.ptr(seed.y, seed.x);    
    pforbiden_seed = mask_forbiden.ptr(seed.y, seed.x);
    pimg_seed = image_bgr.ptr(seed.y, seed.x);     
    phsv_seed = image_hsv.ptr(seed.y, seed.x);         
}


int Exploration::checkAdjacent(int direction)
{    
    // center pixel in seed
    pixel = seed;
    int step, step3;
    // define steps to get adjacent pixel
    switch (direction)
    {
        case eEAST:
            step = 1;
            step3 = 3;    
            break;
                
        case eSOUTH:
            step = row_step;
            step3 = 3*row_step;    
            break;
                
        case eWEST:
            step = -1;
            step3 = -3;    
            break;
               
        case eNORTH:
            step = -row_step;
            step3 = -3*row_step;    
            break;
    } // end switch
    
    pexplored_pixel = pexplored_seed + step;
    // if not explored
    if (*pexplored_pixel == 0)
    {
        *pexplored_pixel = EXPLORED_VALUE;
        pforbiden_pixel = pforbiden_seed + step;
        pregion_pixel = pregion_seed + step; // move pixel even if it's forbidden to allow whole border marking
        // move pixel to specified direction
        movePixel(direction);
        // if not forbidden, get data
        if (*pforbiden_pixel == 0)                         
        {
            state = Exploration::eFREE;
            pimg_pixel = pimg_seed + step3; 
            phsv_pixel = phsv_seed + step3; 
        }
        else
            state = Exploration::eFORBIDEN;
    }
    else
        state = Exploration::eEXPLORED;
    
    return state;
}


void Exploration::movePixel(int direction)
{    
    switch (direction)
    {
        case eEAST:
            pixel.x++;
            if (pixel.x > xmax)                    
                xmax = pixel.x;
            break;
                
        case eSOUTH:
            pixel.y++;
            if (pixel.y > ymax)                            
                ymax = pixel.y;
            break;
                
        case eWEST:
            pixel.x--;
            if (pixel.x < xmin)                            
                xmin = pixel.x;
           break;
               
        case eNORTH:
            pixel.y--;
            if (pixel.y < ymin)                            
                ymin = pixel.y;
            break;
    } // end switch
}

void Exploration::getPixelRGB(cv::Vec3b& rgb_color)
{
    // transform image BGR to pixel's RGB	
    rgb_color[0] = *(pimg_pixel+2);        
    rgb_color[1] = *(pimg_pixel+1);
    rgb_color[2] = *pimg_pixel;    
}


void Exploration::getSeedRGB(cv::Vec3b& rgb_color)
{
    // transform image BGR to seed's RGB	
    rgb_color[0] = *(pimg_seed+2);        
    rgb_color[1] = *(pimg_seed+1);
    rgb_color[2] = *pimg_seed;    
}


void Exploration::getPixelHSV(cv::Vec3i& hsv_color)
{
    // hue/2 is stored in the image (with byte depth)
    hsv_color[0] = 2*(*phsv_pixel);
    hsv_color[1] = *(phsv_pixel+1);
    hsv_color[2] = *(phsv_pixel+2);
}


void Exploration::getSeedHSV(cv::Vec3i& hsv_color)
{
    // hue/2 is stored in the image (with byte depth)
    hsv_color[0] = 2*(*phsv_seed);
    hsv_color[1] = *(phsv_seed+1);
    hsv_color[2] = *(phsv_seed+2);
}


void Exploration::markPixelAccepted()
{  
    // pixel accepted -> marked as region and forbidden
     *pregion_pixel = Body::BODY_VALUE;														
     *pforbiden_pixel = EXPLORED_VALUE;
}

void Exploration::markPixelRejected()
{  
     // pixel rejected -> marked as border (used by later merge process)
    *pregion_pixel = Body::BORDER_VALUE;														             
}

// Must be called at the end of each exploration process.
// Computes the final explored window.
void Exploration::computeWindow()
{
    window.x = xmin;
    window.y = ymin;
    window.width = xmax - xmin + 1;
    window.height = ymax - ymin + 1;
}

}
