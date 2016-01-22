#ifndef __GOON_DATA_VSHAPE_H
#define __GOON_DATA_VSHAPE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
namespace goon 
{
 class vShape
{     
 private:
        float shape_factor;     // is never < 1.0

 public:
//     vShape ();
//     ~vShape();

    float getShapeFactor() {return shape_factor;}
    void setShapeFactor(float value) {shape_factor=value;}    
};  
}  
#endif
