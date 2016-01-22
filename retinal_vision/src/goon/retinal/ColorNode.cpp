/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/retinal/ColorNode.h"

namespace goon
{
// constructor
ColorNode::ColorNode ()
{  
    pcolor = 0;
    psamples = 0;
    pupdates = 0;
    
    // build list of sorround windows (one for each node type)        
    cv::Rect window;        
    for (int i=0; i<eTYP_DIM; i++)
    {
        computeSorroundWindow(i, window);
        vec_windows.push_back(window);
    }
}

// destructor
ColorNode::~ColorNode()
{
}


void ColorNode::setInfo(int itype, cv::Vec3f& local_color, cv::Vec2s& node_data)
{
    type = itype;
    pcolor = &local_color;
    psamples = &(node_data[eDAT_SAMPLES]);
    pupdates = &(node_data[eDAT_UPDATES]);
}


// It's valid only if it has samples.
bool ColorNode::validLocal()
{
    return ((*psamples) != 0);    
}


cv::Rect& ColorNode::getSorroundWindow()
{
    return vec_windows.at(type);
}


void ColorNode::computeSorroundWindow(int itype, cv::Rect& window)
{
    switch (itype)
    {
        case eTYP_INT:
            window = cv::Rect(-1, -1, 3, 3);            
            break;
        case eTYP_N:
            window = cv::Rect(-1, 0, 3, 2);            
            break;
        case eTYP_S:
            window = cv::Rect(-1, -1, 3, 2);            
            break;
        case eTYP_E:
            window = cv::Rect(-1, -1, 2, 3);            
            break;
        case eTYP_W:
            window = cv::Rect(0, -1, 2, 3);            
            break;
        case eTYP_NE:
            window = cv::Rect(-1, 0, 2, 2);            
            break;
        case eTYP_NW:
            window = cv::Rect(0, 0, 2, 2);            
            break;
        case eTYP_SE: 
            window = cv::Rect(-1, -1, 2, 2);            
            break;
        case eTYP_SW:
            window = cv::Rect(0, -1, 2, 2);            
            break;
    }                    
}

}
