#ifndef __GOON_DATA_MODEL_H
#define __GOON_DATA_MODEL_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/features/ColorBlob.h"
#include "goon/features/nature/Nature.h"

namespace goon 
{
// Class used to represent a body model, the symbolic representation of a visual body.
// It's the basic unit of object models.
// It extends from ColorBlob (like Body class).
class Model : public ColorBlob
{
protected:
    int ID;
    cv::Rect window;   // relative to object model
    Nature oNature;

public:    
    Model();
    //~Model();

    int getID() {return ID;};
    cv::Rect& getWindow() {return window;};
    Nature& getNature() {return oNature;};    

    void setID(int value) {ID = value;};
    void setWindow(cv::Rect& window) {this->window = window;};    

    virtual void clear();

    virtual std::string toString();    
    virtual std::string shortDesc();    
};
}
   
  
#endif
