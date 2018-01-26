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
    
    addFeature("retinal: multi-threaded segmentation (4 threads) + merge", true);
    addFeature("peripheral: rois detection + motion perception", true);
    addFeature("focus: color saliency + interest position", true);
    addFeature("binding: target ROI window", true);
    addFeature("characterization: global + local + structure", false);
    addFeature("recognition: ", false);    
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
        desc += *it_feature + ", activated : " + std::to_string(*it_activation) + "\n";
        it_feature++;
        it_activation++;        
    }
    desc += "speed = " + std::to_string(speed) + " fps";

    return desc;
}

}
