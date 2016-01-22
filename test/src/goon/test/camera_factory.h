#ifndef __GOON_CAMERA_FACTORY_H
#define __GOON_CAMERA_FACTORY_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>

#include "goon/camera/camera.h"

namespace goon 
{
// Class to create a specific camera object
class CameraFactory
{
private:
    static log4cxx::LoggerPtr logger;

public:
    enum eOption
    {
        eCAM_WEBCAM,
        eCAM_IPCAM,
        eCAM_WIFIBOT_WIRELESS,
        eCAM_ALBARRACIN,
        eCAM_SOUTHERN_BEACH,
        eVIDEO_CAMPUS_HALL,
        eIMAGE_CAMPUS_HALL1,
        eIMAGE_CAMPUS_HALL2,
        eIMAGE_CAMPUS_HALL3,
        eIMAGE_CAMPUS_HALL4,
        eIMAGE_BABOON,
        eIMAGE_FRUITS,
        eIMAGE_JLUIS,
        eOPTIONS_DIM
    };

    // factory method to create different types of camera objects
    static Camera* createCamera (int option);
};
}																
#endif
