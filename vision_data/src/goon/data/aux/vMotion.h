#ifndef __GOON_DATA_VMOTION_H
#define __GOON_DATA_VMOTION_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
namespace goon 
{
 class vMotion
{
 private:
    static const float K180_DIV_PI;  // constant 180/PI
    float speed_x;    // pixels/sec
    float speed_y;    // pixels/sec
    float angle;     // degrees (0 at east, up positive, down negative)        
    float speed;    // pixels/sec

 public:
     vMotion ();
     ~vMotion();

    float getSpeedX () {return speed_x;};
    float getSpeedY () {return speed_y;};
    float getAngle () {return angle;};
    float getSpeed () {return speed;};
     
    void computeSpeeds(int xtrans, int ytrans, float time_millis);
};  
}  
#endif
