#ifndef __GOON_CORTEX_RECALL_H
#define __GOON_CORTEX_RECALL_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>
#include <vector>
#include <log4cxx/logger.h>

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
    static log4cxx::LoggerPtr logger;
    int ID;   // ID of last added model
    std::vector<ObjectModel> listRecalledModels;    // models recalled from LT memory
    std::vector<ObjectModel> listLearnedModels;    // models learned from visual input
    VisualMemory oVisualMemory;
    int searchFrom;    // range beginning for models search in LT memory
    int searchSize;     // range size for models search in LT memory
                
public:
    Recall();
    ~Recall();

    std::vector<ObjectModel>& getRecalledModels() {return listRecalledModels;};
    std::vector<ObjectModel>& getLearnedModels() {return listLearnedModels;};

    // clears the lists of models
    void clear();
    // resets search range in LT memory
    void resetSearch();

    // adds the given model to the learned models list
    void addLearnedModel(ObjectModel& oObjectModel);           

    // fetches a new range of object models from long term memory
    void recallModels(ObjectModel& oObjectModel);       

    // stores all learned models in LT memory
    void storeModels();

    // returns description of all models
    std::string toString();    
    // returns short description of all models
    std::string shortDesc();                    
};
}    
#endif

        