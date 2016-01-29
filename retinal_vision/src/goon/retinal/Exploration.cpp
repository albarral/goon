/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/retinal/Exploration.h"

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
         mask_roi = cv::Scalar(0,0,0);        
         mask_roi = mask_region(window);
         mask_roi = cv::Scalar(0,0,0);        
    }    
}

void Exploration::setForbiddenMask(cv::Mat& mask_segmented)
{
    mask_forbiden =  mask_segmented;    
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


int Exploration::checkAdjacent(int location)
{    
    pixel = seed;
    state = Exploration::eFREE;
    
    switch (location)
    {
        case eEAST:
                pexplored_pixel = pexplored_seed + 1;
                // not explored
                if (*pexplored_pixel == 0)
                {
                    *pexplored_pixel = 255;
                    pforbiden_pixel = pforbiden_seed + 1;
                    pixel.x++;
                    if (pixel.x > xmax)                    
                        xmax = pixel.x;
                    // not forbiden
                    if (*pforbiden_pixel == 0)                         
                    {
                        pimg_pixel = pimg_seed + 3; 
                        phsv_pixel = phsv_seed + 3; 
                        pregion_pixel = pregion_seed + 1;                         
                    }
                    else
                        state = Exploration::eFORBIDEN;
                }
                else
                    state = Exploration::eEXPLORED;
                break;
                
        case eSOUTH:
                pexplored_pixel = pexplored_seed + row_step;
                // not explored
                if (*pexplored_pixel == 0)
                {
                    *pexplored_pixel = 255;
                    pforbiden_pixel = pforbiden_seed + row_step; 						
                    pixel.y++;
                    if (pixel.y > ymax)                            
                        ymax = pixel.y;
                    // not forbiden
                    if (*pforbiden_pixel == 0)                         
                    {
                        pimg_pixel = pimg_seed + 3*row_step; 
                        phsv_pixel = phsv_seed + 3*row_step; 
                        pregion_pixel = pregion_seed + row_step;                         
                    }
                    else
                        state = Exploration::eFORBIDEN;
                }
                else
                    state = Exploration::eEXPLORED;
                break;
                
        case eWEST:
                pexplored_pixel = pexplored_seed - 1;
                // not explored
                if (*pexplored_pixel == 0)
                {
                    *pexplored_pixel = 255;
                    pforbiden_pixel = pforbiden_seed - 1; 						
                    pixel.x--;
                    if (pixel.x < xmin)                            
                        xmin = pixel.x;
                    // not forbiden
                    if (*pforbiden_pixel == 0)                         
                    {
                        pimg_pixel = pimg_seed - 3;                    
                        phsv_pixel = phsv_seed - 3; 
                        pregion_pixel = pregion_seed - 1; 
                    }
                    else
                        state = Exploration::eFORBIDEN;
                }
                else
                    state = Exploration::eEXPLORED;
               break;
               
        case eNORTH:
                pexplored_pixel = pexplored_seed - row_step;
                // not explored
                if (*pexplored_pixel == 0)
                {
                    *pexplored_pixel = 255;
                    pforbiden_pixel = pforbiden_seed - row_step; 	
                    pixel.y--;
                    if (pixel.y < ymin)                            
                        ymin = pixel.y;
                    // not forbiden
                    if (*pforbiden_pixel == 0)                         
                    {
                        pimg_pixel = pimg_seed - 3*row_step; 
                        phsv_pixel = phsv_seed - 3*row_step; 
                        pregion_pixel = pregion_seed - row_step; 
                    }
                    else
                        state = Exploration::eFORBIDEN;
               }
                else
                    state = Exploration::eEXPLORED;
                break;
    } // end switch
    
    return state;
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


void Exploration::markPixel(bool baccepted)
{  
    // pixel accepted -> marked as region and forbidden
     if (baccepted)
    {
         *pregion_pixel = 255;														
         *pforbiden_pixel = 255;
     }
     // pixel rejected -> marked as border (used by later merge process)
     else
         *pregion_pixel = 1;														             
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
