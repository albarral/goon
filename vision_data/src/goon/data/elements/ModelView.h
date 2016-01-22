#ifndef __GOON_DATA_MODELVIEW_H
#define __GOON_DATA_MODELVIEW_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/aux/VisualElement.h"
#include "goon/data/aux/Record.h"

namespace goon 
{
// This class represents a model view.
// It holds info about the model view in 2 areas: 
// - appearance (inherits from VisualElement)
// - history (inherits from Record).
class ModelView : public VisualElement, public Record
{
public:        
    enum ePointOfView
    {
         ePOV_UNKNOWN, 
         ePOV_FRONT, 
         ePOV_BACK, 
         ePOV_LEFT_SIDE, 
         ePOV_RIGHT_SIDE, 
         ePOV_TOP, 
         ePOV_BOTTOM,
         ePOV_DIM
    };	

private:
    int pov;    // point of view
    
public:    
    ModelView();
     //~ModelView();

    int getPOV() {return pov;};       
    void setPOV (int value);    
};
}
#endif
