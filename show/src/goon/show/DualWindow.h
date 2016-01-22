#ifndef __GOON_SHOW_DUALWINDOW_H
#define __GOON_SHOW_DUALWINDOW_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "opencv2/core/core.hpp"

namespace goon 
{
// This class shows a window with two images side by side.
class DualWindow
{       
private:
    cv::Size size;          // size of single image (total size = (2*width, height)    
    cv::Mat image;         // image shown 
    cv::Mat imageL;     // left side roi
    cv::Mat imageR;     // right side roi
    
public:
    DualWindow();       

    // returns the dual image
    cv::Mat& getImage() {return image;};
    
    // updates the partial size of the dual window
    void reSize(int singleW, int singleH); 

    // Sets the image to be shown on the left 
    void setImageLeft (cv::Mat& image);

    // Sets the image to be shown on the right
    void setImageRight (cv::Mat& image);
    
    // Show the dual image (in a window, video or gallery)
    void show(int output = 0);

private:    
    // scales an image down to the single size and return the result
    cv::Mat scaleDown(cv::Mat& image);
};
}    
#endif
