/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include <vector>

#include "opencv2/imgproc/imgproc.hpp"          // for cvtColor

#include "goon/main/test/Test.h"
#include "goon/core/VisualData.h"
#include "goon/camera/Grabber.h"
#include "goon/retinal/merge.h"
#include "goon/retinal/Segmenter.h"
#include "goon/show/monitor/RetinaSaver.h"
#include "tuly/utils/Environment.h"

using namespace log4cxx;

namespace goon
{    
LoggerPtr Test::logger(Logger::getLogger("goon.main"));
    
void Test::testMaskAcces()
{        
    LOG4CXX_INFO(logger, "\n\nTest mask access ...\n");    

    int w = 640;
    int h = 480;

    cv::Mat mask = cv::Mat::zeros(h, w, CV_8UC1); 
    
    cv::Point point(w, h);  // BAD LOCATION
    int value = mask.at<uchar>(point.y, point.x);
    
    LOG4CXX_INFO(logger, "value = " << value);    
}

void Test::testSegmentation()
{        
    LOG4CXX_INFO(logger, "\nTest segmentation ...");    

    VisualData oVisualData;        
    Grabber oGrabber;   // utility class used for frame grabbing from any source    
    oGrabber.connect2Image(tuly::Environment::getHomePath() + "/TESTS/images/image_orange3.jpg");
    if (oGrabber.grab())            
    {
        cv::Mat imageCam = oGrabber.getCapture();
        // convert to HSV space
        cv::Mat imageHSV;        
        cv::cvtColor(imageCam, imageHSV, CV_BGR2HSV);
        
        int imgW = imageCam.cols;
        int imgH = imageCam.rows;

        // compute minimum detail size
        float MIN_DETAIL = 0.001;        // regions accepted from at least 0.1% of image area
        int minDetailSize = imgH * imgW * MIN_DETAIL;   
        int samples = 1;

        // create the segmentation mask (to be shared by all segmenters)
        cv::Mat mask_segmented = cv::Mat::zeros(imgH, imgW, CV_8UC1); 
        cv::Point p1(100, 150);
        cv::Point p2(300, 150);
        std::vector<cv::Point> listSeeds1 = {p1};
        std::vector<cv::Point> listSeeds2 = {p2};   
        // segmenter 1
        Segmenter oSegmenter1;
        oSegmenter1.setID(1);
        oSegmenter1.init(oVisualData.getRetina(), mask_segmented);
        oSegmenter1.config(listSeeds1, samples, minDetailSize);
        oSegmenter1.setFrequency(100);   // to wait small delays
        // segmenter 2
        Segmenter oSegmenter2;
        oSegmenter2.setID(2);
        oSegmenter2.init(oVisualData.getRetina(), mask_segmented);
        oSegmenter2.config(listSeeds2, samples, minDetailSize);         
        oSegmenter2.setFrequency(100);   // to wait small delays
        
        oSegmenter1.on();
        oSegmenter2.on();
        // wait till both segmenters are ready
        while (!oSegmenter1.isReady() || !oSegmenter2.isReady())
        {
            usleep(10000); // 10ms        
        }

        int beat1 = oSegmenter1.getBeat();
        int beat2 = oSegmenter2.getBeat();
        oSegmenter1.newRequest(imageCam, imageHSV);
        oSegmenter2.newRequest(imageCam, imageHSV);        
        
        // wait till both segmenters are finished
        while (oSegmenter1.getBeat() == beat1 || oSegmenter2.getBeat() == beat2)
        {
            usleep(10000); // 10ms        
        }

        // show retina description
        LOG4CXX_INFO(logger, oVisualData.getRetina().shortDesc());
        
        oSegmenter1.off();
        oSegmenter2.off();
        oSegmenter1.wait();
        oSegmenter2.wait();        
     
//        Merge oMerge;
//        oMerge.init(imgW, imgH);
//        oMerge.doMerge(oVisualData.getRetina());

        showRetina(imageCam, oVisualData.getRetina());
    }
    LOG4CXX_INFO(logger, "Test finished");    
}

void Test::showRetina(cv::Mat& imageCam, Retina& oRetina)
{
    std::string folder = tuly::Environment::getHomePath() + "/TESTS/VISION";    
    // clean folder
    tuly::Environment::cleanFolder(folder);
    // save region images
    RetinaSaver oRetinaSaver;
    oRetinaSaver.setDestinationFolder(folder);           
    oRetinaSaver.saveRegions(imageCam, oRetina.getListRegions());   

    std::list<Region>::iterator itRegion = oRetina.getListRegions().begin();
    Body oBorder1 = getBorderFromRegion(*itRegion);
    std::string filename = "border1";            
    oRetinaSaver.saveBody(imageCam, oBorder1, itRegion->getRGB(), filename, 1);
    
    itRegion++;
    Body oBorder2 = getBorderFromRegion(*itRegion);
    filename = "border2";            
    oRetinaSaver.saveBody(imageCam, oBorder2, itRegion->getRGB(), filename, 2);
}

Body Test::getBorderFromRegion(Region& oRegion)
{
    Body oBody;
    cv::Mat maskBorder = oRegion.computeBorderMask();
    //cv::Rect window = oRegion.getWindow();
    cv::Rect window(0, 0, maskBorder.cols, maskBorder.rows);
    oBody.setMaskAndWindow(maskBorder, window);
    
    return oBody;
}
}