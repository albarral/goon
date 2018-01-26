#ifndef __GOON_MAIN_VERSION_H
#define __GOON_MAIN_VERSION_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

namespace goon
{
class GoonVersion
{
private:
    std::string version;
    std::string date;
    int speed;      // processing speed (fps)
    std::vector<std::string> listFeatures;
    std::vector<bool> listActivations;

public:
    GoonVersion();
    ~GoonVersion();

    void addFeature(std::string desc, bool bactivated);
    
    std::string toString();
};
}

#endif
