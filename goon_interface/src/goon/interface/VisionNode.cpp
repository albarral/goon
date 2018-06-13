/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/interface/VisionNode.h"
#include "goon/interface/topics/FocusTopic.h"
#include "tron2/robot/common/ExtraTopic.h"
#include "tron2/robot/RobotSystem.h"

namespace goon
{    
const std::string VisionNode::VISION_FOCUS = "focus";

VisionNode::VisionNode() : Node(tron2::RobotSystem::eNODE_VISION, tron2::RobotSystem::VISION_NODE)
{
    fillTopics();
}

void VisionNode::fillTopics()
{
    // build topics map
    addCode(eVISION_FOCUS, VISION_FOCUS);
    addCode(tron2::Node::eEXTRA_TOPIC, tron2::Node::EXTRA_TOPIC);
}

tron2::Topic* VisionNode::getTopic4Channel(int channel)
{                
    switch (channel)
    {
        case eVISION_FOCUS_CHANNEL:
        {
            return new FocusTopic();
            break;
        }            
        case eVISION_EXTRA_CHANNEL: 
        {
            return new tron2::ExtraTopic();
            break;
        }            
        default:
            return nullptr;
    }        
}        

}