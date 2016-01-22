/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/aux/VisualElement.h"
	
namespace goon 
{
// constructor
VisualElement::VisualElement ()
{
    visual_type = eVIS_REGION;
}

void VisualElement::addSubElement(VisualElement& vElement, cv::Vec2f rel_pos, float rel_scale)
{  
    subElements.push_back(vElement);    
    
    cv::Vec3f dist = {rel_pos[0], rel_pos[1], rel_scale};

    mat_dist.push_back(dist);

    if (visual_type == eVIS_REGION)
        visual_type = eVIS_STRUCTURE;
}

}
