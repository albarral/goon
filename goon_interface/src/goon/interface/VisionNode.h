#ifndef __GOON_INTERFACE_VISIONNODE_H
#define __GOON_INTERFACE_VISIONNODE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Node.h"
#include "tron2/robot/Topic.h"

namespace goon
{
// Definition of vision node topics
 class VisionNode : public tron2::Node
{
public:
    /*! vision topics */
    enum eVisionTopics
    {
        eVISION_FOCUS,                /*! focus topic */
        eVISION_DIM
    };

    /*! vision node channels */
    enum eVisionChannels
    {
        eVISION_FOCUS_CHANNEL,             /*! focus channel */
        eVISION_EXTRA_CHANNEL,              /*! extra channel  */
        eVISION_CHANNELS_DIM
    };

    /*! vision topic names */
    static const std::string VISION_FOCUS;

 public:     
     VisionNode();

     static tron2::Topic* getTopic4Channel(int channel);  
     
private:
     virtual void fillTopics();
};
}
#endif
