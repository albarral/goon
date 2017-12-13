#ifndef __GOON_RETINAL_COLOR_NODE_H
#define __GOON_RETINAL_COLOR_NODE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include "opencv2/core/core.hpp"

namespace goon
{
class ColorNode
{        
public:
    // Data stored in grid data
    enum eData
    {
        eDAT_SAMPLES,
        eDAT_UPDATES,
    };

    // Node type due to its position in the grid 
    // (1 internal, 4 side borders and 4 corners)
    enum eType
    {
         eTYP_INT,
         eTYP_N, 
         eTYP_S, 
         eTYP_E, 
         eTYP_W, 
         eTYP_NE, 
         eTYP_NW, 
         eTYP_SE, 
         eTYP_SW, 
         eTYP_DIM,
    };	

private:
    int type;                         // type of node  
    cv::Vec3f* pcolor;           // (pointer to) node's local color
    short* psamples;                      // (pointer to) node's local samples
    short* pupdates;                       // (pointer to) node's updates
    std::vector<cv::Rect> vec_windows;     // list of sorround windows for different node types
    
public:

    ColorNode();
    ~ColorNode();    
    
    // Sets the node's info (type, color, data ...)
    void setInfo(int itype, cv::Vec3f& local_color, cv::Vec2s& node_data);

    int getType() {return type;}
            
    // Returns the node's local color.
    cv::Vec3f& getColor() {return *pcolor;};
    // Checks if the node has a valid local color. 
    bool validLocal();           
    short& getSamples() {return *psamples;};    
    short& getUpdates() {return *pupdates;};   
    
    // Returns this node's sorround window
    cv::Rect& getSorroundWindow();    

private:    
    // Computes the sorround window around a node of the specified type
    void computeSorroundWindow(int itype, cv::Rect& window);    
};
		  	    		  
}  
  
#endif
