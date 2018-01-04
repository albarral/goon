#ifndef __GOON_RETINAL_COLOR_GRID_H
#define __GOON_RETINAL_COLOR_GRID_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#include "goon/retinal/ColorNode.h"

namespace goon
{
class ColorGrid
{
private:
    int GRID_STEP;       // separation between grid nodes (in pixels)
    int rows;
    int cols;
    cv::Mat map_nodes;               // map of nodes corresponding to each image pixel (row, col, type)
    cv::Mat gridColor;          // matrix of nodes with local color info (rgb)
    cv::Mat gridData;                // matrix of nodes with other info (samples & updates)
    int sel_row;                     // row of selected node
    int sel_col;                      // column of selected column  
    ColorNode oNode;           // info of selected node
    cv::Mat mask_samples;       // mask version of the samples channel in grid_data
    
public:

    ColorGrid();
    ~ColorGrid();

    void setGridStep(int grid_step);    
    // resizes the grid
    void resize(int img_w, int img_h);    
    
    // clears all grid nodes
    void clear();

    // Obtains the node at which the specified point belongs
    ColorNode& selectNode(cv::Point& point);
    
    // Computes the local color in the selected node.
    void getLocalColor(cv::Vec3f& rgb_color);

    // Updates the region's local color adding a new sample to the grid.
    void updateLocalColor(const cv::Vec3b& rgb_color);
    
    // computes the grid's mean color inside the specified window.
    cv::Vec3f computeMeanColor(cv::Rect& window);
    // compute the grid window associated to to the specified window
    cv::Rect computeGridWindow(cv::Rect& window);
    
    cv::Mat& getColorGrid() {return gridColor;}           
    cv::Mat getMassGrid();

    cv::Mat& getMaskSamples() {return mask_samples;}
        
private:
    // Notifies the neighbour nodes about a local color change.
    // void notifyNeighbours();    
        
    // Checks the type of node depending on its position in the grid. 
    int checkType(int row, int col);
};
		  	    		  
}  
#endif
