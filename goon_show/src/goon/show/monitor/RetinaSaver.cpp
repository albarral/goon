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
    imgExtension = ".jpg";
}

void RetinaSaver::setDestinationFolder(std::string path)
{
    this->path = path;            
}

void RetinaSaver::saveRegions (cv::Mat& image_cam, std::list<Region>& listRegions)
{    
    oDraw.setSize(image_cam);
    
    // draw each segmented region in a separate file
    for (Region& oRegion: listRegions) 
    {
//        // skip simple regions
//        if (oRegion.getType() == Region::eREG_SIMPLE)
//            continue;
        
        oDraw.clearBackGround();
        // draw masks
        oDraw.setExactColor(oRegion.getRGB());
        oDraw.drawMask (oRegion.getMask(), oRegion.getWindow());
        oDraw.drawWindow (oRegion.getWindow());

        // draw centroids
        int* pos = oRegion.getPos();
        cv::Point centroid(pos[0], pos[1]);                        
        oDraw.drawPoint(centroid, tivy::Draw::eRED, 3);

        // draw ID's
        oDraw.drawNumber(oRegion.getID(), centroid);                        

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
        std::string filePath = path + "/" + filename + std::to_string(oRegion.getID()) + imgExtension;
        cv::imwrite(filePath, oDraw.getOutput()); 

//      cv::Point& seed = oRegion.getSeed();
//      oDrawRet.drawPoint(seed, tivy::Draw::eYELLOW);
    }
}

}