/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream> 
#include <list>   

#include <opencv2/opencv.hpp>

#include "TestRegions.h"
#include "goon/data/retina.h"
#include "goon/data/base/region.h"
#include "goon/retinal/merge.h"
#include <goon/features/color/rgb_color.h>
#include "goon/monitor/RetinaMonitor.h"

namespace goon
{    

void TestRegions::testMerge() 
{        
    std::cout << "TEST REGIONS ..." << std::endl;

    int w = 640;
    int h = 480;

    Retina oRetina, oRetina2;
    
    RetinaMonitor oRetinaMonitor, oRetinaMonitor2;
    cv::Mat imageCam = cv::Mat(h, w, CV_8UC3);
    cv::Mat imageRegions, imageMerge;

    // windows
    int base = 50; 
    int alt = 50;     
    cv::Rect window1 = cv::Rect (0, 0, base, alt);
    cv::Rect window2 = cv::Rect (0, 25, base, alt);
    cv::Rect window3 = cv::Rect (100, 0, base*2, alt);

    // masks
    cv::Mat mask1 = cv::Mat (h, w, CV_8U);
    cv::Mat mask2 = cv::Mat (h, w, CV_8U);
    cv::Mat mask3 = cv::Mat (h, w, CV_8U);
    cv::Mat grid = cv::Mat::ones(h/10, w/10, CV_16U);
   
    // paint masks
    cv::Mat maskROI = mask1(window1);    
    maskROI.setTo(255);
    maskROI = mask2(window2);    
    maskROI.setTo(255);
    maskROI = mask3(window3);    
    maskROI.setTo(255);
    
    // create regions, assign ID/mask/window/grid
    Region oRegion1, oRegion2, oRegion3;
    oRegion1.setID(0);
    oRegion1.setMaskAndWindow(mask1, window1);
    oRegion1.setGrid(grid);
    oRegion2.setID(1);
    oRegion2.setMaskAndWindow(mask2, window2);
    oRegion2.setGrid(grid);
    oRegion3.setID(2);
    oRegion3.setMaskAndWindow(mask3, window3);
    oRegion3.setGrid(grid);

    // compute blobs
    oRegion1.computeMass();
    oRegion1.computeBlob();
    oRegion2.computeMass();
    oRegion2.computeBlob();
    oRegion3.computeMass();
    oRegion3.computeBlob();

    // set colors
    cv::Vec3f redColor = {255, 0, 0};
    oRegion1.setRGB(redColor);
    RGBColor::toHSV(oRegion1.getRGB(), oRegion1.getHSV());
    oRegion2.setRGB(redColor);
    RGBColor::toHSV(oRegion2.getRGB(), oRegion2.getHSV());
    oRegion3.setRGB(redColor);
    RGBColor::toHSV(oRegion3.getRGB(), oRegion3.getHSV());
                
    oRetina.addRegion(oRegion1);
    oRetina.addRegion(oRegion2);
    oRetina.addRegion(oRegion3);

    
    // Retina2
    oRetina2 = oRetina;
    
    Merge oMerge;
    oMerge.doMerge(oRetina2);
    
//    Region oRegion4;
//    oRegion4 = oRegion3;
//    oRegion4.merge(oRegion2);
//    oRegion4.merge(oRegion1);
    
//    std::list<Region> listRegions2;
//    listRegions2.push_back(oRegion4);

    // draw
    oRetinaMonitor.drawRegions(imageCam, oRetina.getListRegions());               
    imageRegions = oRetinaMonitor.getOutput();   
    oRetinaMonitor2.drawRegions(imageCam, oRetina2.getListRegions());               
    imageMerge = oRetinaMonitor2.getOutput();   

    cv::namedWindow("regions");         
    cv::namedWindow("merge");         
    
    cv::imshow("regions", imageRegions);           
    cv::imshow("merge", imageMerge);           
    cv::waitKey(0); // wait for keyb interaction
}

}