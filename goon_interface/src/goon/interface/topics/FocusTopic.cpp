/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/interface/topics/FocusTopic.h"
#include "goon/interface/VisionNode.h"

namespace goon
{
FocusTopic::FocusTopic() : Topic(VisionNode::eVISION_FOCUS, VisionNode::VISION_FOCUS)
{
    fillConcepts();    
}

void FocusTopic::fillConcepts()
{
    addCode(eFOCUS_SHIFT, FOCUS_SHIFT);
    addCode(eFOCUS_MODE, FOCUS_MODE);                         
}
}