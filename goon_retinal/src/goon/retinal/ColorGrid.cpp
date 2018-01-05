/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream>
#include <cmath>

#include "goon/retinal/ColorGrid.h"
#include "goon/retinal/ConfigRetinal.h"
#include <maty/math/average.h>

namespace goon
{
// constructor
ColorGrid::ColorGrid ()
{        
}

// destructor
//ColorGrid::~ColorGrid()
//{
//}


void ColorGrid::clear () 
{
    // clear the grids
    gridColor = cv::Mat::zeros(rows, cols, CV_32FC3);        // r, g, b
    gridData = cv::Mat::zeros(rows, cols, CV_16SC2);                 // samples, updates (specified in ColorNode.h)
    sel_row = sel_col = -1;
}


ColorNode& ColorGrid::selectNode(cv::Point& point)
{
    cv::Vec3b& node = getNode4Point(point);
    
    // if we select a different node, update its values
    if (node[0] != sel_row || node[1] != sel_col)
    {
        sel_row = node[0]; 
        sel_col = node[1];
        
        oColorNode.setInfo(node[2], gridColor.at<cv::Vec3f>(sel_row, sel_col), gridData.at<cv::Vec2s>(sel_row, sel_col));

        // if the node's sorround has changed, update its sorround color value
//        if (oNode.getSorroundUpdates() != 0)
//        {            
//            updateSorroundColor();            
//        }
    }
    
    return (oColorNode);
}


// Computes the local color in the selected node.
void ColorGrid::getLocalColor(cv::Vec3f& rgb_color)
{
    cv::Vec3f* Color;
    cv::Vec2s* Data;
    cv::Vec3f avg = {0, 0, 0};
    int node_samples, total_samples = 0;
    
    // check the node's neighbourhood 
    cv::Rect window = oColorNode.getSorroundWindow();
    window += cv::Point(sel_col, sel_row);
    cv::Mat roi_local_color = gridColor(window);
    cv::Mat roi_data = gridData(window);        
         
    // walk the neighbourhood building the weighted average color
    for (int i=0; i<window.height; i++)
    {
        Color = roi_local_color.ptr<cv::Vec3f>(i);
        Data = roi_data.ptr<cv::Vec2s>(i);

        for (int j=0; j<window.width; j++)
        {
            node_samples = Data[j][ColorNode::eDAT_SAMPLES];
            // if active node, sum its local color
            if (node_samples != 0)
            {
                avg += node_samples*Color[j];
                total_samples += node_samples;
            }
        }	
    }
    
    // compute the average
    if (total_samples != 0)
    {
        avg = avg * (1.0 / total_samples);
    }

    rgb_color = avg;    
    
//    rgb_color = grid_local_color.at<cv::Vec3f>(sel_row, sel_col);    
}


// Updates the region's local color adding a new sample to the corresponding node.
void ColorGrid::updateLocalColor (const cv::Vec3b& rgb_color)
{
    short& local_samples = oColorNode.getSamples();
    
    local_samples++;
    maty::Average::updateWithSample(oColorNode.getColor(), rgb_color, local_samples);
}


// Notifies the nodes around the selected one that their sorround color has changed.
//void ColorGrid::notifyNeighbours()
//{
//    cv::Vec4s* Data;
//    bool bsafe_row;
//
//    // establish the node's neighbourhood 
//    cv::Rect window = oNode.getSorroundWindow();
//    int avoid_row = -window.y;
//    int avoid_col = -window.x;    
//    cv::Point center = cv::Point(oNode.getCol(), oNode.getRow());
//    cv::Mat roi_data = grid_data(window + center);
//    
//    // mark the sorrounding nodes as changed
//    for (int i=0; i<window.height; i++)
//    {
//        Data = roi_data.ptr<cv::Vec4s>(i);
//        bsafe_row = (i != avoid_row);
//
//        for (int j=0; j<window.width; j++)
//        {
//            // skip the original node
//            if (bsafe_row || j != avoid_col)
//                Data[j][ColorNode::eDAT_SORROUND_UPDATES] = 1;
//        }	
//    }
//}


cv::Vec3f ColorGrid::computeMeanColor(cv::Rect& window)
{
    cv::Rect gridWindow = computeGridWindow(window);
    
    cv::Mat gridColorROI = gridColor(gridWindow);
    cv::Mat gridDataROI = gridData(gridWindow);

    // We need to extract the local_samples channel from grid_data
    cv::Mat gridMass(gridDataROI.rows, gridDataROI.cols, CV_16SC1);
    cv::Mat out[] = {gridMass};
    int from_to[] = {0,0};
    cv::mixChannels (&gridDataROI, 1, out, 1, from_to, 1);
    
    // And convert it to a mask, in order to compute the mean
    gridMass.convertTo(mask_samples, CV_8UC1);
    cv::Scalar color = cv::mean(gridColorROI, mask_samples);
    
    cv::Vec3f rgbColor = cv::Vec3f(color[0], color[1], color[2]);
    return rgbColor;
}

cv::Mat ColorGrid::getMassGrid()
{
    cv::Mat planes[2];
    cv::split(gridData, planes);  
    return planes[0];
}
}
