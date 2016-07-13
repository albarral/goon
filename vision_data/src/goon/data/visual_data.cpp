/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>

#include "goon/data/visual_data.h"

namespace goon 
{
// Constructor
VisualData::VisualData ()
{    
}

// Destructor
VisualData::~VisualData ()
{
}

void VisualData::storeRetinaPhoto()
{
    std::lock_guard<std::mutex> locker(mutex1);
    // clone retina
    oRetina2 = oRetina;    
}

void VisualData::storeROIsPhoto()
{
    std::lock_guard<std::mutex> locker(mutex2);
    // clone ROIS 
    oROIs2 = oROIs;    
}

Retina& VisualData::getRetina2()
{
    std::lock_guard<std::mutex> locker(mutex1);
    return oRetina2;    
}  

Rois& VisualData::getROIs2()
{
    std::lock_guard<std::mutex> locker(mutex2);
    return oROIs2;    
}

}

