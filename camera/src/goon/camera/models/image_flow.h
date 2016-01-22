#ifndef __GOON_IMAGE_FLOW_H
#define __GOON_IMAGE_FLOW_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/camera/camera.h"

namespace goon 
{
// This class emulates the image capture process from still images.
// It extends from Camera.
class ImageFlow : public Camera
{
    private:
        static log4cxx::LoggerPtr logger;
        bool bread;     // indicates if the image has been read
        
public:
    ImageFlow (std::string path);
    ~ImageFlow();

    // emulates connection by checking the address exists
    int connect();

    // capture new frame
    int grab();

};
}
	
#endif
	
