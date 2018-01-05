#ifndef __GOON_RETINAL_COLOR_GRID_H
#define __GOON_RETINAL_COLOR_GRID_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

#include "goon/retinal/ColorNode.h"
#include "goon/retinal/Grid.h"

namespace goon
{
class ColorGrid : public Grid
{
private:
    cv::Mat gridColor;          // matrix of nodes with local color info (rgb)
    cv::Mat gridData;                // matrix of nodes with other info (samples & updates)
    int sel_row;                     // row of selected node
    int sel_col;                      // column of selected column  
    ColorNode oColorNode;           // info of selected node
    cv::Mat mask_samples;       // mask version of the samples channel in grid_data
    
public:

    ColorGrid();
    //~ColorGrid();

    cv::Mat& getColorGrid() {return gridColor;}           
    cv::Mat getMassGrid();
    cv::Mat& getMaskSamples() {return mask_samples;}        

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
};
		  	    		  
}  
#endif
