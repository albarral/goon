/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/nature/Nature.h"

namespace goon
{
// Constructor
Nature::Nature ()
{
    category = 0;
    type = 0;
    ID = 0;
    name = "";
}

std::string Nature::toString()
{
    std::string desc = "Nature [category = " + std::to_string(category) + 
            ", type = " + std::to_string(type) + 
            ", ID = " + std::to_string(ID) + 
            ", name = " + name + "]"; 
    return desc;
}

}
