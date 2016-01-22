/***************************************************************************
 *   Copyright (C) 2015 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/show/ImageSave.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr ImageSave::logger(Logger::getLogger("goon.show"));
// Constructor
ImageSave::ImageSave ()
{  
    counterVideo = 0;
    counterGallery = 0;
    videoFPS = 30;
    videoExtension = ".avi";
    galleryExtension = ".jpg";
    size = cv::Size(0,0);    
    
    // default values
    setGallery(true);
    setVideo(false);
    setPath("./");
    setFileName("goonOutput");
}

void ImageSave::setPath(std::string value)
{
    path = value;    
}

void ImageSave::setFileName(std::string fileName)
{
    name = fileName;    
}

void ImageSave::save(cv::Mat& image)
{      
    // save video
    if (bdoVideo)
    {
        if (counterVideo == 0)
        {            
            size = cv::Size(image.cols, image.rows);
            initVideoWritter();
        }

        if (video.isOpened())        
        {
            video << image;        
            counterVideo++;
        }
        else
            LOG4CXX_ERROR(logger, "Video file not open");
    }
    // save new gallery image
    if (bdoGallery)
    {
        std::string fileName = path + "/" + name + std::to_string(counterGallery) + galleryExtension;
        cv::imwrite(fileName, image); 
        counterGallery++;
    }    
}

void ImageSave::reset()
{
    LOG4CXX_INFO(logger, "ImageSave: counters reset!");
    counterVideo = 0;
    counterGallery = 0;
}


//CV_FOURCC('P','I','M','1')    = MPEG-1 codec (AVI))
//CV_FOURCC('M','J','P','G')    = motion-jpeg codec (does not work well)
//CV_FOURCC('M', 'P', '4', '2') = MPEG-4.2 codec
//CV_FOURCC('D', 'I', 'V', '3') = MPEG-4.3 codec
//CV_FOURCC('D', 'I', 'V', 'X') = MPEG-4 codec
//CV_FOURCC('U', '2', '6', '3') = H263 codec
//CV_FOURCC('I', '2', '6', '3') = H263I codec
//CV_FOURCC('F', 'L', 'V', '1') = FLV1 codec
// Opens a videowriter object with the appropriate features (double width if dual mode requested)
void ImageSave::initVideoWritter ()
{        
    std::string fileName = path + "/" + name + videoExtension;
    int format = CV_FOURCC('P','I','M','1');    // avi
    
    LOG4CXX_INFO(logger, "Initializing video file: " << fileName);

    // close any open video
//    if (video.isOpened())
//        video.release();
            
    video.open(fileName, format, videoFPS, size, true);            

    if (!video.isOpened())
        LOG4CXX_ERROR(logger, "Could not open video file");
}



}