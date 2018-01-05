#ifndef __GOON_RETINAL_GRID_H
#define __GOON_RETINAL_GRID_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

namespace goon
{
// This class represents a grid over an image.
// A nodes map is created to map image points to grid nodes (the node position in the grid is also mapped).
class Grid
{
public:
    // node location in the grid
    enum eLoc
    {
         eLOC_INTERNAL,  // internal
         eLOC_N,    // north border
         eLOC_S,    // south border
         eLOC_E,    // east border
         eLOC_W,    // west border
         eLOC_NE,   // north east corner     
         eLOC_NW,   // north west corner
         eLOC_SE,   // south east corner
         eLOC_SW,  // south west corner
         eLOC_OUT,  // out of grid
         eLOC_DIM,
    };	
    
protected:
    int GRID_STEP;       // separation between grid nodes (in pixels)
    int rows;       // grid rows
    int cols;       // grid columns
    cv::Mat map_nodes;   // map of nodes corresponding to each image pixel (row, col, type)
    
public:
    Grid();
    ~Grid();

    int getRows() {return rows;};
    int getCols() {return cols;};
    
    // resizes the grid
    void setSize(int img_w, int img_h, int grid_step);    
    
    cv::Vec3b& getNode4Point(cv::Point& point);

    // checks node location in the grid (eLoc) 
    int checkNodeLocation(int row, int col);

    // compute the grid window associated to to the specified image window
    cv::Rect computeGridWindow(cv::Rect& window);                
};
		  	    		  
}  
#endif
