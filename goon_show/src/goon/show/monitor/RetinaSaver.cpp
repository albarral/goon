/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdlib.h>
#include <opencv2/highgui/highgui.hpp>

#include "goon/show/monitor/RetinaSaver.h"

namespace goon 
{
RetinaSaver::RetinaSaver()
{
    path = std::getenv("HOME");    
    //imgExtension = ".jpg";
    imgExtension = ".bmp";
}

void RetinaSaver::setDestinationFolder(std::string path)
{
    this->path = path;            
}

void RetinaSaver::saveRegions (cv::Mat& imageCam, std::list<Region>& listRegions, bool bdrawCentroid)
{    
    // draw each segmented region in a separate file
    for (Region& oRegion: listRegions) 
    {
//        // skip simple regions
//        if (oRegion.getType() == Region::eREG_SIMPLE)
//            continue;
  
        // save file        
        std::string filename; 
        switch (oRegion.getType())
        {
            case Region::eREG_SIMPLE:
            case Region::eREG_COLLECTION:
                filename = "region_";
                break;
            case Region::eREG_MERGED:
                filename = "xregion_";
                break;
        }
        filename += std::to_string(oRegion.getID());
        
        saveBody(imageCam, oRegion, oRegion.getRGB(), filename, oRegion.getID(), bdrawCentroid);
    }
}

void RetinaSaver::saveBody(cv::Mat& imageCam, Body& oBody, cv::Vec3f& rgbColor, std::string name, int ID, bool bdrawCentroid)
{
    oDraw.setSize(imageCam);
    
    oDraw.clearBackGround();
    // draw mask
    oDraw.setExactColor(rgbColor);
    oDraw.drawMask(oBody.getMask(), oBody.getWindow());
    //oDraw.drawWindow(oBody.getWindow());

    // draw centroid
    if (bdrawCentroid)
    {
        oDraw.drawPoint(oBody.getPos(), tivy::Draw::eRED, 3);
        // draw ID
        oDraw.drawNumber(ID, oBody.getPos());                        
    }

    std::string filePath = path + "/" + name + imgExtension;
    cv::imwrite(filePath, oDraw.getOutput()); 

    //      cv::Point& seed = oBody.getSeed();
    //      oDrawRet.drawPoint(seed, tivy::Draw::eYELLOW);    
}
}