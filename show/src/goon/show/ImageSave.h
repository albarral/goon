#ifndef __GOON_SHOW_IMG_SAVE_H
#define __GOON_SHOW_IMG_SAVE_H

/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include <log4cxx/logger.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>        // for video writter    

namespace goon 
{
// This class allows saving images both as video files and/or gallery of images.
class ImageSave 
{    
private:
    static log4cxx::LoggerPtr logger;
    bool bdoVideo;        // when true, images are stored as a video file
    bool bdoGallery;     // when true, images are stored as a gallery
    int counterVideo;
    int counterGallery;
    std::string path;      // path where files are stored
    std::string name;    // name of stored file (for gallery mode the counter value is added to the final name)
    int videoFPS;              // frames per second of video file
    std::string videoExtension;    // extension of video file
    std::string galleryExtension;    // extension of image files in gallery
    cv::Size size;              // size of saved images        
    cv::VideoWriter video;   // opencv video writer object    
    
public:
    ImageSave();

    // sets a new path value for video and gallery
    void setPath (std::string value);
    // sets the filename value for video and gallery
    void setFileName (std::string value);
    
    // activates/deactivates video mode
    void setVideo(bool value) {bdoVideo = value;};
    // activates/deactivates gallery mode
    void setGallery(bool value) {bdoGallery = value;};
    // saves given image in video file or gallery
    void save(cv::Mat& image);
    // sets a new frames per second value for video
    //void setVideoFPS (int value);
    // resets the counters 
    void reset();
    
private:
    // creates a new video writer object
    void initVideoWritter();
};
}    
#endif
