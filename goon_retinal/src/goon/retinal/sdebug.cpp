/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
  ***************************************************************************/

#include "goon/retinal/sdebug.h"
				 				 				 					
namespace goon
{
// constructor
SDebug::SDebug ()
{
    num_iterations = 0;
    max_iterations = 1000;
}

// destructor
SDebug::~SDebug()
{
}


void SDebug::init(int w, int h, int gstep)
{        
    oShowWindow.init(Show::eMOD_SINGLE, "segmentation");
    oShowVideo.init(Show::eMOD_SINGLE, "/home/albarral/TESTS/segmentation_out", w, h);
    
    img_w = w;
    img_h = h;
    grid_step = gstep;
}


void SDebug::setBase(cv::Mat& image)
{
    oDraw.setBackGround(image);
    showGrid2();
}


void SDebug::storeInfo(cv::Rect exp_window, cv::Vec3f seg_color, cv::Mat exp_mask)
{
    window = exp_window;
    rgb_color = seg_color;
    exp_mask.copyTo(mask);    
}


void SDebug::drawInfo()
{
    oDraw.setExactColor(rgb_color);
    oDraw.drawMask (mask, window);
    //oDraw.drawPoint(seed, Draw::eYELLOW);

    oShowWindow.setRight(oDraw.getOutput());
    oShowVideo.setRight(oDraw.getOutput());
    oShowWindow.show();
    oShowVideo.show();    
}


bool SDebug::checkProgress()
{
    bool breached = false;
    
    num_iterations++;
    if (num_iterations == max_iterations)
    {
        breached = true;
        num_iterations = 0;
    }
    
    return breached;
}


void SDebug::showGrid()
{
    int row, col;
    
    oDraw.setDefaultColor(Draw::eWHITE);
        
    row = grid_step/2;
    while (row < img_h)
    {
        oDraw.drawHLine(row);
        
        row += grid_step;        
    }
    
    col = grid_step/2;
    while (col < img_w)
    {
        oDraw.drawVLine(col);
        
        col += grid_step;        
    }
}


void SDebug::showGrid2()
{
    int row, col;
    cv::Point node;
    
    for (row = grid_step/2; row < img_h; row += grid_step)
    {
        node.y = row;
        
        for (col = grid_step/2; col < img_w; col += grid_step)
        {
            node.x = col;

            oDraw.drawPoint(node, Draw::eBLACK, 1);
        }
    }
}

}
