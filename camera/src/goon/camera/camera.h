#ifndef __GOON_CAMERA_H
#define __GOON_CAMERA_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <opencv2/opencv.hpp>

namespace goon 
{
// Base class for camera
class Camera
{
protected:
    std::string address;
    bool bconnected;
    cv::Mat image;
    int img_w;         // width of camera image (in pixels)
    int img_h;         // height of camera image (in pixels)
    int counter;        // frame counter
    float visualField;      // camera's horizontal visual field (in degrees)
    int height;              // vertical distance between the camera and the floor (in centimeters)

public:
    Camera ();
    //~Camera();
    
    std::string getAddress() {return address;}
    
    bool isConnected() {return bconnected;}

    // Gets pointer to captured image
    cv::Mat& getCapture() {return image;};
    // Gets a copy of the captured image
    void getCaptureCopy (cv::Mat* image_dest);    
    
    int getImgWidth() {return img_w;};
    int getImgHeight() {return img_h;};
    int getCounter (){return counter;};

    void setVisualField (float value) {visualField = value;};
    float getVisualField () {return visualField;};
    
    void setCamHeight (int value) {height = value;};
    int getCamHeight () {return (height);};

    // connect to camera 
    virtual int connect() = 0;
    // capture new frame
    virtual int grab() = 0;
};
}
	
#endif
	
