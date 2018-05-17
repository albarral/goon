/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/peripheral/Saliency.h"
#include "tron/cv/average.h"
#include "tron/math/Coordinates.h"

using namespace log4cxx;

namespace goon 
{
LoggerPtr Saliency::logger(Logger::getLogger("goon.peripheral"));

Saliency::Saliency()
{
    mode = Saliency::eSALIENCY_COLOR;    
}

Saliency::~Saliency()
{
    listSalients.clear();
}

void Saliency::setMode(int value)
{
    // check if valid mode
    if (value >= 0 && value < Saliency::eSALIENCY_DIM)
        mode = value;
}

void Saliency::computeSaliency(std::list<ROI>& listROIs)
{
    // reset list
    listSalients.clear();

    // reset averages 
    avgSat = avgValue = avgSpeed = 0.0;
        
    // compute the average values of all detected ROIs 
    std::list<ROI>::iterator it_roi = listROIs.begin();
    std::list<ROI>::iterator it_end = listROIs.end();    
    int sample = 0;
    while (it_roi != it_end)
    {
        sample++;
        
        cv::Vec3f& hsv = it_roi->getHSV();
        tron::Average::updateWithSample(avgSat, (int)hsv[1], sample);
        tron::Average::updateWithSample(avgValue, (int)hsv[2], sample);
                
        it_roi++;
    }    

    stSalient salient;
    // compute the differences of each ROI to the average values (and also the saliency)
    it_roi = listROIs.begin();    
    while (it_roi != it_end)
    {
        cv::Vec3f& hsv = it_roi->getHSV();

        salient.roiID = it_roi->getID();
        salient.difSat = fabs(hsv[1] - avgSat);
        salient.difValue = fabs(hsv[2] - avgValue);
        salient.difSpeed = 0.0; 
        salient.saliency = computeSaliency(salient);
        
        // and add it to the salients list 
        listSalients.push_back(salient);
                
        it_roi++;
    }    
}

//void Saliency::computeSpeed(ROI& oROI)
//{
//        cv::Vec2f& speed = oROI.getMotion().getSpeed();
//        float absSpeed, angle;
//        tron::Coordinates::cartesian2polar(speed[0], speed[1], absSpeed, angle);
//        // speed > 0.1 pixels/ms (100 pixels/s))
//        int color = tivy::Draw::eYELLOW;
//        if (absSpeed > 0.01)
//            color = tivy::Draw::eRED;            
//    
//}

float Saliency::computeSaliency(stSalient& salient)
{
    switch (mode)
    {
        case Saliency::eSALIENCY_COLOR:    
//            return salient.difSat * salient.difValue;
            return salient.difSat;
            break;

        case Saliency::eSALIENCY_MOVEMENT:
            return salient.difSpeed;
            break;

        case Saliency::eSALIENCY_DUAL:
            return salient.difSat * salient.difValue * salient.difSpeed;
            break;
            
        default: 
            return 0.0;
            break;
    }
}

stSalient& Saliency::getMostSalient()
{
    int maxPos = 0;
    float max = 0.0;
    
    // find salient with max saliency
    int pos = 0;
    for (stSalient& salient : listSalients)
    {
        if (salient.saliency > max)
        {
            max = salient.saliency;
            maxPos = pos;
        }
        pos++;
    }
    
    return listSalients.at(maxPos);
}

std::string Saliency::toString(stSalient& salient)
{
    std::string desc = "stSalient [id = " + std::to_string(salient.roiID) + 
            ", difSat = " + std::to_string(salient.difSat) + 
            ", difValue = " + std::to_string(salient.difValue) + 
            ", difSpeed = " + std::to_string(salient.difSpeed) + 
            ", saliency = " + std::to_string(salient.saliency) + "]";
    
    return desc;
}

}