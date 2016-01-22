#ifndef __GOON_DATA_VISUAL_ELEMENT_H
#define __GOON_DATA_VISUAL_ELEMENT_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <vector>
#include <opencv2/core/core.hpp>

#include "goon/data/aux/vColor.h"
#include "goon/data/aux/vShape.h"
//#include "goon/data/aux/vTexture.h"

namespace goon 
{
// This class represents an object's appearance.
// It holds info such as: color, shape, texture and structure.
class VisualElement 
{
public:        
    enum eTypes
    {
         eVIS_REGION, 
         eVIS_STRUCTURE
    };	

protected:
    int visual_type;
    vColor color;
    vShape shape;
    //vTexture texture;
    std::vector<VisualElement> subElements;    
    cv::Mat mat_dist;           // spatial distribution of subelements (4 columns, one for each corner)
    
public:    
    VisualElement();
     //~VisualElement();
    
    bool isRegion() {return (visual_type == eVIS_REGION);}
    bool isStructure() {return (visual_type == eVIS_STRUCTURE);}

    vColor& getColor() {return color;}

    vShape& getShape() {return shape;};
    
    //vTexture& getTexture() {return texture;};     
    
    std::vector<VisualElement>& getSubElements() {return subElements;};
    void addSubElement(VisualElement& vElement, cv::Vec2f rel_pos, float rel_scale);
    
    cv::Mat& getMatDistribution() {return mat_dist;}
};
}
#endif
