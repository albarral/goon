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
    cv::Mat grid_local_rgb;          // matrix of nodes with local color info (rgb)
    cv::Mat grid_data;                // matrix of nodes with other info (samples & updates)
    cv::Rect grid_window;          // grid window equivalent to the exploration window     
    cv::Vec3f mean_rgb;         // mean color of the grid   
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
    
    // Computes the grid's mean color inside the specified image window.
    void computeMeanColor(cv::Rect& window);
            
    cv::Rect& getGridWindow() {return grid_window;}    
    cv::Vec3f& getColorMean () {return mean_rgb;}    
    cv::Mat& getLocalGrid() {return grid_local_rgb;}    
    cv::Mat& getMaskSamples() {return mask_samples;}
       
    // extracts samples channel from grid_data
    cv::Mat getSamplesGrid();
        
private:
    // Notifies the neighbour nodes about a local color change.
    // void notifyNeighbours();    
        
    // Checks the type of node depending on its position in the grid. 
    int checkType(int row, int col);
};
		  	    		  
}  
#endif
