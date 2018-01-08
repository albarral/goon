/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <cmath>

#include "goon/retinal/Grid.h"

namespace goon
{
// constructor
Grid::Grid ()
{        
    rows = cols = 0;    
    GRID_STEP = 10;
}

// destructor
Grid::~Grid()
{
}

void Grid::setSize(int img_w, int img_h, int grid_step)
{
    int row, col;
    GRID_STEP = grid_step;
    // (+ 1) because the grid must cover the image borders
    rows = img_h/GRID_STEP + 1;	
    cols = img_w/GRID_STEP + 1;
    
    // if grid side exceeds 255 recompute grid step to & limit it
    if (rows > 255 || cols > 255)
    {
        if (img_w > img_h)
        {            
            GRID_STEP = img_w / 254;
        }
        else
            GRID_STEP = img_h / 254;
            
        rows = img_h/GRID_STEP + 1;	
        cols = img_w/GRID_STEP + 1;        
    }
    
    map_nodes = cv::Mat(img_h, img_w, CV_8UC3);     // (row, col, location) depth valid for images up to 2500x2500        

    // build the map of nodes 
    for (int i=0; i<img_h; i++)
    {
        row = std::round((float)i / GRID_STEP);        

        cv::Vec3b* MapRow = map_nodes.ptr<cv::Vec3b>(i); 
        
        for (int j=0; j<img_w; j++)
        {    
            col = std::round((float)j / GRID_STEP);    

            MapRow[j][0] = row;
            MapRow[j][1] = col;
            MapRow[j][2] = checkNodeLocation(row, col);
        }
    }            
}

cv::Vec3b& Grid::getNode4Point(cv::Point& point)
{    
    return map_nodes.at<cv::Vec3b>(point.y, point.x);
}


cv::Rect Grid::computeGridWindow(cv::Rect& window)
{
    // check & correct window limits for safe grid computation
    if (window.x + window.width >= map_nodes.cols)
        window.width = map_nodes.cols - window.x - 1;
    if (window.y + window.height >= map_nodes.rows)
        window.height = map_nodes.rows - window.y - 1;
    
    // translate the image window to a grid window
    cv::Vec3b& node1 = map_nodes.at<cv::Vec3b>(window.y, window.x);
    cv::Vec3b& node2 = map_nodes.at<cv::Vec3b>(window.y + window.height, window.x + window.width);    
    return (cv::Rect(node1[1], node1[0], node2[1]-node1[1], node2[0]-node1[0]));        
}

// Checks the type of node depending on its position in the grid. 
int Grid::checkNodeLocation(int row, int col)
{        
    int location;

    // check if out of grid
//    if (row >= rows || col >= cols)
//        return Grid::eLOC_OUT;
    
    bool btop = (row == 0);
    bool bbottom = (row == rows-1);
    bool bleft = (col == 0);
    bool bright = (col == cols-1);
    
    // if not in border -> internal
    if (!btop && !bbottom && !bleft && !bright)
        location = Grid::eLOC_INTERNAL;
    // in a border
    else
    {        
        // TOP border
        if (btop)
        {
            if (bleft) 
                location = Grid::eLOC_NW;
            else if (bright)
                location = Grid::eLOC_NE;
            else
                location = Grid::eLOC_N;            
        }
        // BOTTOM border
        else if (bbottom)
        {
            if (bleft) 
                location = Grid::eLOC_SW;
            else if (bright)
                location = Grid::eLOC_SE;
            else
                location = Grid::eLOC_S;                        
        }
        // MIDDLE row
        else
        {
            if (bleft) 
                location = Grid::eLOC_W;
            else if (bright)
                location = Grid::eLOC_E;            
        }
    }   
    
    return location;
}

}
