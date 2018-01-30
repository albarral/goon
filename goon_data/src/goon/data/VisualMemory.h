#ifndef __GOON_DATA_VISUAL_MEMORY_H
#define __GOON_DATA_VISUAL_MEMORY_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "goon/data/cortex/ObjectModel.h"

namespace goon 
{
class VisualMemory
{
    private:
        std::vector<ObjectModel> listModels;
        int ID;   // ID of last added model
                
    public:
        VisualMemory();
        ~VisualMemory();

        std::vector<ObjectModel>& getListModels() {return listModels;};
        int getNumModels() {return listModels.size();};
         // clears the lists of models
        void clear();

        // adds a new object model to the list
        void addObjectModel (ObjectModel& oObjectModel);           
        
        // returns description of all models
        std::string toString();    
        // returns short description of all models
        std::string shortDesc();                    
};
}    
#endif

        