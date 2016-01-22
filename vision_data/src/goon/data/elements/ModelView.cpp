/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/elements/ModelView.h"
	
namespace goon 
{
// constructor
ModelView::ModelView ()
{
    pov = ePOV_UNKNOWN;
}

void ModelView::setPOV(int value)
{
    if (value > 0 && value < ePOV_DIM)
        pov = value;
    else
        pov = ePOV_UNKNOWN;
}
}
