/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/cortex/recognition/Recall.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr Recall::logger(Logger::getLogger("goon.cortex.recognition"));

// Constructor
Recall::Recall ()
{    
    ID = 0;    
    searchFrom = 0;    
    searchSize = 20;    // default size of search range 20 
}

// Destructor
Recall::~Recall ()
{
    clear();
}

void Recall::clear()
{  
    ID = 0;
    searchFrom = 0;    
    listRecalledModels.clear();
    listLearnedModels.clear();
}

void Recall::resetSearch()
{
    LOG4CXX_TRACE(logger, "Recall::resetSearch");
    // reset search range
    searchFrom = 0;    
    // clear recalled models
    listRecalledModels.clear();
}

void Recall::addLearnedModel(ObjectModel& oObjectModel)
{
    LOG4CXX_TRACE(logger, "Recall::addLearnedModel");
    oObjectModel.setID(ID++);
    listLearnedModels.push_back(oObjectModel);
}  

void Recall::recallModels(ObjectModel& oObjectModel)
{
    LOG4CXX_TRACE(logger, "Recall::recallModels");
    
    // access LT memory (temporally simulated by VisualMemory)
    std::vector<ObjectModel>& listLTModels = oVisualMemory.getListModels();
    int sizeLT = listLTModels.size();
    // set fetch range
    int end = searchFrom + searchSize;
    if (end > sizeLT)
        end = sizeLT;
    
    // skip if end of LT memory reached
    if (searchFrom >= sizeLT)            
    {
        LOG4CXX_WARN(logger, "Recall.fetchModels: no recall, LT memory end reached");
        return;
    }

    LOG4CXX_DEBUG(logger, "fetch models: " << searchFrom << " - " << end);

    // fetch LT models and add them to recalled list
    for (int i=searchFrom; i<end; i++) 
    {            
        ObjectModel& oRecalledModel = listLTModels.at(i);
        listRecalledModels.push_back(oRecalledModel);
    }    
}

void Recall::storeModels()
{
    LOG4CXX_TRACE(logger, "Recall::storeModels");
    // stores all learned models in LT memory
    std::vector<ObjectModel>& listLTModels = oVisualMemory.getListModels();
    listLTModels.insert(listLTModels.end(), listLearnedModels.begin(), listLearnedModels.end());    
}


std::string Recall::toString()
{
    std::string desc = "Recall:\n";
    desc += "recalled models ...\n";
    std::vector<ObjectModel>::iterator it_model = listRecalledModels.begin();
    // walk list
    while (it_model != listRecalledModels.end())
    {            
        desc += it_model->toString() + "\n";
        it_model++;
    }
    
    desc += "learned models ...\n";
    it_model = listLearnedModels.begin();
    // walk list
    while (it_model != listLearnedModels.end())
    {            
        desc += it_model->toString() + "\n";
        it_model++;
    }
    return desc;
}

std::string Recall::shortDesc()
{
    std::string desc = "Recall:\n";
    desc += "recalled models ...\n";
    std::vector<ObjectModel>::iterator it_model = listRecalledModels.begin();
    // walk list
    while (it_model != listRecalledModels.end())
    {            
        desc += it_model->shortDesc() + "\n";
        it_model++;
    }
    
    desc += "learned models ...\n";
    it_model = listLearnedModels.begin();
    // walk list
    while (it_model != listLearnedModels.end())
    {            
        desc += it_model->shortDesc() + "\n";
        it_model++;
    }
    return desc;
}

}

