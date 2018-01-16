/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <unistd.h>
#include <vector>

#include <opencv2/highgui/highgui.hpp>

#include "goon/main/test/Test.h"
#include "goon/retinal/merge.h"
#include "goon/show/monitor/RetinaSaver.h"
#include "tuly/utils/Environment.h"

using namespace log4cxx;

namespace goon
{    
LoggerPtr Test::logger(Logger::getLogger("goon.main"));
    
void Test::testMaskAcces()
{        
    LOG4CXX_INFO(logger, "\n\nTest mask access ...\n");    

    int w = 20;
    int h = 20;

    cv::Mat mask = cv::Mat::zeros(h, w, CV_8UC1); 
    
    cv::Point point(10, 5);
    int value = mask.at<uchar>(point.y, point.x);
    
    LOG4CXX_INFO(logger, "value = " << value);        
}

void Test::testSegmentation()
{        
    LOG4CXX_INFO(logger, "\nTest segmentation ...");    

    bool bdual = true; // dual segmentation
    
    VisualData oVisualData;        
    TestImage oTestImage;
//    oTestImage.createImage(20,20);
//    bool bok = true;
    bool bok = oTestImage.loadImage();
    if (bok)            
    {
        // get test images & mask segmented
        cv::Mat imageCam = oTestImage.getImageCam();
        cv::Mat imageHSV = oTestImage.getImageHSV();        
        cv::Mat mask_segmented = oTestImage.getMaskSegmented();
        
        // compute minimum detail size
        float MIN_DETAIL = 0.001;        // regions accepted from at least 0.1% of image area
        int minDetailSize = imageCam.cols * imageCam.rows * MIN_DETAIL;   
        minDetailSize = 1;
        int samples = 1;
                
        // segmenter 1
        Segmenter oSegmenter1;
        oSegmenter1.setID(1);
        oSegmenter1.init(oVisualData.getRetina(), mask_segmented);
        // segmenter 2
        Segmenter oSegmenter2;
        if (bdual)
        {
            oSegmenter2.setID(2);
            oSegmenter2.init(oVisualData.getRetina(), mask_segmented);
        }

        // launch segmenters
        //cv::Point seed1(10, 10);
        cv::Point seed1(100, 150);
        cv::Point seed2(300, 150);
        bok = launchSegmenter(oSegmenter1, imageCam, imageHSV, seed1, samples, minDetailSize);
        if (bok && bdual)
            bok = launchSegmenter(oSegmenter2, imageCam, imageHSV, seed2, samples, minDetailSize);
        
        // wait for segmenter jobs done
        if (bok)
            waitSegmenterFinished(oSegmenter1);
        if (bok && bdual)
            waitSegmenterFinished(oSegmenter2);

        // show retina description
        LOG4CXX_INFO(logger, oVisualData.getRetina().shortDesc());
        
        Merge oMerge;
        oMerge.init(imageCam.cols, imageCam.rows);
        oMerge.doMerge(oVisualData.getRetina());

        showRetina(imageCam, oVisualData.getRetina());
    }
    LOG4CXX_INFO(logger, "Test finished");    
}

bool Test::launchSegmenter(Segmenter& oSegmenter, cv::Mat& imageCam, cv::Mat& imageHSV, cv::Point& seed, int samples, int detail)
{
    if (seed.x >= imageCam.cols || seed.y >= imageCam.rows)
    {
        LOG4CXX_WARN(logger, "Segmenter not launched, seed out of bounds!");           
        return false;
    }
    
    // prepare segmenter
    std::vector<cv::Point> listSeeds = {seed};
    oSegmenter.config(listSeeds, samples, detail);
    oSegmenter.setFrequency(100);           

    // launch segmenter thread
    oSegmenter.on();
    // wait till segmenter is ready to work
    while (!oSegmenter.isReady())
    {
        usleep(10000); // 10ms        
    }

    // and request image processing
    oSegmenter.newRequest(imageCam, imageHSV);    

    return true;
}

void Test::waitSegmenterFinished(Segmenter& oSegmenter)
{
    // wait till segmenter has finished its work
    while (oSegmenter.getBeat() == 0)
    {
        usleep(10000); // 10ms        
    }

    // and ask it to end
    oSegmenter.off();
    oSegmenter.wait();
}

void Test::showRetina(cv::Mat& imageCam, Retina& oRetina)
{
    std::string folder = tuly::Environment::getHomePath() + "/TESTS/VISION";    
    // clean folder
    tuly::Environment::cleanFolder(folder);
    // save region images
    RetinaSaver oRetinaSaver;
    oRetinaSaver.setDestinationFolder(folder);           
    oRetinaSaver.saveRegions(imageCam, oRetina.getListRegions(), false);   

    // save region borders
    std::list<Region>::iterator itRegion = oRetina.getListRegions().begin();
    for (int i=0; i<oRetina.getNumRegions(); i++)
    {
        Body oBorder = getBorderFromRegion(*itRegion);
        std::string filename = "border" + std::to_string(i);            
        oRetinaSaver.saveBody(imageCam, oBorder, itRegion->getRGB(), filename, i, false);    
        itRegion++;
    }
    
    // save camera image
    std::string filePath = folder + "/image.bmp";
    cv::imwrite(filePath, imageCam);     
}

Body Test::getBorderFromRegion(Region& oRegion)
{
    Body oBody;
    cv::Mat maskBorder = oRegion.computeBorderMask();
    // the border mask is translated to (0,0) as comes from the region mask
    // so to create a body of the border the window must start at (0,0)
    cv::Rect borderWindow = oRegion.getWindow();
    borderWindow.x = borderWindow.y = 0;
    oBody.setMaskAndWindow(maskBorder, borderWindow);
    // but finally move window to original position to be coherent with region
    cv::Rect& bodyWindow = oBody.getWindow();
    bodyWindow += cv::Point(oRegion.getWindow().x, oRegion.getWindow().y);
    
    return oBody;
}
}