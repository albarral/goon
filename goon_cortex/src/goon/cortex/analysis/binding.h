#ifndef __GOON_CORTEX_BINDING_H
#define __GOON_CORTEX_BINDING_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <log4cxx/logger.h>
#include <opencv2/core/core.hpp>

#include "goon/data/retina.h"
#include "goon/data/cortex/Object.h"


namespace goon
{
class Binding
{
private:
    static log4cxx::LoggerPtr logger;
    float bindObjectFraction;

public:
    Binding();
    //~Binding();
 		
    void formObject(Object& oObject, Retina* pRetina, cv::Rect& window);
 };
}
#endif
