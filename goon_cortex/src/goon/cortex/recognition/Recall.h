#ifndef __GOON_CORTEX_RECALL_H
#define __GOON_CORTEX_RECALL_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>

#include "goon/data/cortex/ObjectModel.h"
#include "goon/data/VisualMemory.h"

namespace goon 
{
// This class manages the visual recall. 
// It fetches models from the long term memory to be used in the recognition process.
// It also adds new models to the long term memory related to new learned objects.
class Recall
{
    private:
        int ID;   // ID of last added model
        std::vector<ObjectModel> listRecalledModels;
        std::vector<ObjectModel> listNewModels;
        VisualMemory oVisualMemory;
                
    public:
        Recall();
        ~Recall();

        std::vector<ObjectModel>& getRecalledModels() {return listRecalledModels;};
        std::vector<ObjectModel>& getNewModels() {return listNewModels;};

        // clears the lists of models
        void clear();

        // adds the given model to the new models list
        void addNewModel(ObjectModel& oObjectModel);           
        
        // fetches a new series of object models from long term memory
        void fetchModels(ObjectModel& oObjectModel, int start);       
        
        // fixes all new models and those recalled models that have been updated
        void fixModels();
        
        // returns description of all models
        std::string toString();    
        // returns short description of all models
        std::string shortDesc();                    
};
}    
#endif

        