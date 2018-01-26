/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/main/GoonVersion.h"
		
namespace goon
{
GoonVersion::GoonVersion()
{
    version = "0.1";
    date = "8/3/2016";
    speed = 5; 
    
    addFeature("retinal: \t multi-threaded segmentation (4 threads) + merge", true);
    addFeature("peripheral: \t rois detection + motion perception", true);
    addFeature("focus: \t color saliency + interest position", true);
    addFeature("binding: \t target ROI window", true);
    addFeature("characterization: \t global + local + structure", false);
    addFeature("recognition: \t ", false);    
}

GoonVersion::~GoonVersion()
{
    listFeatures.clear();
    listActivations.clear();
}

void GoonVersion::addFeature(std::string desc, bool bactivated)
{
    listFeatures.push_back(desc);
    listActivations.push_back(bactivated);
}

std::string GoonVersion::toString()
{
    std::string desc = "GoonVersion: " + version + " - " + date + "\n";
    
    std::vector<std::string>::iterator it_feature = listFeatures.begin();
    std::vector<bool>::iterator it_activation = listActivations.begin();
    // walk lists
    while (it_feature != listFeatures.end() && it_activation != listActivations.end())
    {            
        desc += *it_feature + " - \t activated : " + std::to_string(*it_activation) + "\n";
        it_feature++;
        it_activation++;        
    }
    desc += "speed = " + std::to_string(speed) + " fps";

    return desc;
}

}
