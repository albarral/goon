/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
				
#include "goon/cortex/recognition/Evidence.h"
#include "goon/data/config/CortexConfig.h"
							
using namespace log4cxx;

namespace goon
{
LoggerPtr Evidence::logger(Logger::getLogger("goon.cortex.recognition"));

// Constructor
Evidence::Evidence()
{
    CortexConfig oCortexConfig;    
    sensitivity = oCortexConfig.getEVIDENCE_SENSITIVITY();
}

//Evidence::~Evidence ()
//{
//}


bool Evidence::checkSelfEvidence(ObjectModel& oObjectModel)
{
    LOG4CXX_TRACE(logger, "Evidence.checkSelfEvidence");
    
    bool bmatched;
    // safety check
    if (oObjectModel0.getMass() > 0)
    {
        // compare object model and candidate model
        float quality = oCompare.compareObjectModels(oObjectModel, oObjectModel0);        
        float maxQuality = oCompare.getMaxPossibleQuality();

        LOG4CXX_DEBUG(logger, "Evidence: " << oCompare.showCorrespondences());
        LOG4CXX_DEBUG(logger, "Evidence: quality = " + std::to_string(quality) + ", max quality = " + std::to_string(maxQuality));

        // if matching quality is high enough, the object is the same
        if (quality >= sensitivity*maxQuality)
        {                
            bmatched = true;
            match.quality = quality;
            match.objectMatchedFraction = oCompare.getMatchedFration1();
            match.modelMatchedFraction = oCompare.getMatchedFration2();
        }
        else
            bmatched = false;
    }
    else
        bmatched = false;
    
    // store present model for next iteration
    oObjectModel0 = oObjectModel;

    return bmatched;
}

std::string Evidence::showResult()
{
    std::string text = "evidence: ";
    text += "quality = " + std::to_string(match.quality)
            + ", object matched fraction = " + std::to_string(match.objectMatchedFraction)
            + ", model matched fraction = " + std::to_string(match.modelMatchedFraction) + "\n";
    return text;
}

}
