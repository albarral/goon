/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/data/cortex/Model.h"

namespace goon 
{
Model::Model ()
{
    clear();
}

void Model::clear()
{
    Blob::clear();
    
    ID = -1; 
    window = cv::Rect(0,0,0,0);
}

std::string Model::toString()
{
    std::string desc = "Model [ID = " + std::to_string(ID) + 
            ", window = (" + std::to_string(window.x) + "," + std::to_string(window.y) + "," + std::to_string(window.width) + "," + std::to_string(window.height) + ") " + 
            ", " + oNature.toString() +
            "\n" + ColorBlob::toString();
    return desc;
}

std::string Model::shortDesc()
{
    std::string desc = "Model [ID = " + std::to_string(ID) + " " + ColorBlob::toString();
    return desc;
}

}
