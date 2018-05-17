#ifndef __GOON_CORTEX_CHARACTERIZATION_H
#define __GOON_CORTEX_CHARACTERIZATION_H

/***************************************************************************
 *   Copyright (C) 2010 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <log4cxx/logger.h>

#include "goon/data/cortex/Object.h"

namespace goon
{
class Characterization
{
private:
    static log4cxx::LoggerPtr logger;

public:
    Characterization();
    //~Characterization();

    // compute the global features (shape, centroid, scale and orientation) of the given object as a body
     void checkGlobalObject(Object& oObject);

    // compute the detailed features of the given object as a composition of subbodies following a structural distribution
    void checkObjectDetails(Object& oObject);
};
}
#endif
