#ifndef __GOON_INTERFACE_FOCUSTOPIC_H
#define __GOON_INTERFACE_FOCUSTOPIC_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "tron2/robot/Topic.h"

namespace goon
{
// Concepts definition for the vision focus topic
 class FocusTopic : public tron2::Topic
{
 public:
    /*! focus concepts  */
    enum eConcepts
    {
         eFOCUS_SHIFT,                       /*! shift focus target (bool) */
         eFOCUS_MODE,                       /*! focus mode (int) */
         eFOCUS_DIM
    };

    /*! focus concepts names */
    const std::string FOCUS_SHIFT = "shift";                 /*! shift focus target (bool) */
    const std::string FOCUS_MODE = "mode";                /*! focus mode (int) */

 public:    
    FocusTopic(); 
    
 private: 
    virtual void fillConcepts();      
    
};
}
#endif
