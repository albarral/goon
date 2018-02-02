/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <iostream> 
#include <list>   

#include <opencv2/opencv.hpp>

#include "goon/main/test/TestRegions.h"
#include "goon/data/retina.h"
#include "goon/data/base/region.h"
#include "goon/retinal/merge.h"
#include <goon/features/color/rgb_color.h>
#include "goon/show/monitor/RetinaMonitor.h"

namespace goon
{    

void TestRegions::testMerge() 
{        
    std::cout << "TEST REGIONS ..." << std::endl;

    // this method creates 3 rectangular regions (2 of them overlapping) and puts them into a retina 
    // it then tries to merge the regions, but will not succeed due to the absence of their color grids

    int w = 640;
    int h = 480;

    Retina oRetina, oRetina2;
    
    RetinaMonitor oRetinaMonitor, oRetinaMonitor2;
    cv::Mat imageCam = cv::Mat(h, w, CV_8UC3);
    cv::Mat imageRegions, imageMerge;

    // windows
    int w2 = 50; 
    int h2 = 50;     
    int x1 = 0;
    int x2 = 0;
    int x3 = 100;
    int y1 = 0;
    int y2 = 25;
    int y3 = 0;
    cv::Rect window1 = cv::Rect (x1, y1, w2, h2);
    cv::Rect window2 = cv::Rect (x2, y2, w2, h2);
    cv::Rect window3 = cv::Rect (x3, y3, 2*w2, h2);

    // 3 rectangular masks
    cv::Mat mask = cv::Mat::zeros(h, w, CV_8U);
    cv::Mat mask1 = mask.clone();
    cv::Mat mask2 = mask.clone();
    cv::Mat mask3 = mask.clone();
    mask1(window1).setTo(255);
    mask2(window2).setTo(255);
    mask3(window3).setTo(255);
       
    // create 3 regions 
    Region oRegion1, oRegion2, oRegion3;
    oRegion1.setID(0);
    oRegion1.setMaskAndWindow(mask1, window1);
    oRegion2.setID(1);
    oRegion2.setMaskAndWindow(mask2, window2);
    oRegion3.setID(2);
    oRegion3.setMaskAndWindow(mask3, window3);

    // create regions list
    std::list<Region> listRegions;
    listRegions.push_back(oRegion1);
    listRegions.push_back(oRegion2);
    listRegions.push_back(oRegion3);

    // build retina with the 3 regions
    cv::Vec3f redColor = {255, 0, 0};
    for (Region& oRegion : listRegions)
    {    
        // compute blobs
        oRegion.computeMass();
        oRegion.computeBlob();
        // set colors
        oRegion.setRGB(redColor);
        oRegion.setHSV(RGBColor::toHSV(oRegion1.getRGB()));
        // and add to retina
        oRetina.addRegion(oRegion);
    }
    
    // clone retina to retina2
    oRetina2 = oRetina;
    // merge regions in retina2 (won't merge anything without informed color grids)
    Merge oMerge;
    oMerge.doMerge(oRetina2);
    
    // draw retina1
    oRetinaMonitor.drawRegions(imageCam, oRetina.getListRegions());               
    imageRegions = oRetinaMonitor.getOutput();   
    // draw retina2
    oRetinaMonitor2.drawRegions(imageCam, oRetina2.getListRegions());               
    imageMerge = oRetinaMonitor2.getOutput();   

    cv::namedWindow("regions");         
    cv::namedWindow("merge");         
    
    cv::imshow("regions", imageRegions);           
    cv::imshow("merge", imageMerge);           
    cv::waitKey(0); // wait for keyb interaction
}

}