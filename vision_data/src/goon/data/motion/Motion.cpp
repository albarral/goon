/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <chrono>

#include "goon/data/motion/Motion.h"

namespace goon 
{
// Constructor
Motion::Motion ()
{
    maxMoves = 5;
    avgSpeed[0] = avgSpeed[1] = 0.0;
    avgAccel[0] = avgAccel[1] = 0.0;
}

Motion::~Motion ()
{
    listMoves.clear();
}

void Motion::clear()
{
    avgSpeed[0] = avgSpeed[1] = 0.0;
    avgAccel[0] = avgAccel[1] = 0.0;
    listMoves.clear();    
}

void Motion::update(Move2D& oTransMove)
{
    // add new move and remove oldest one if max size exceeded
    listMoves.push_back(oTransMove);
    if (listMoves.size() > maxMoves)
        listMoves.pop_front();
    
    compute();
}

// computes motion features (average speed & acceleration ...) 
void Motion::compute()
{
    Move2D lastMove = listMoves.back();
    Move2D firstMove = listMoves.front();
    
    std::chrono::duration<int, std::milli> motionInterval = std::chrono::duration_cast<std::chrono::milliseconds>(lastMove.getTimeStamp() - firstMove.getTimeStamp());
    int motionMillis = motionInterval.count();        

    if (motionMillis > 0)
    {
        float factor = 1.0 / motionMillis;
        avgSpeed[0] = (lastMove.getValueX() - firstMove.getValueX()) * factor;
        avgSpeed[1] = (lastMove.getValueY() - firstMove.getValueY()) * factor;
        avgAccel[0] = (lastMove.getSpeedX() - firstMove.getSpeedX()) * factor;
        avgAccel[1] = (lastMove.getSpeedY() - firstMove.getSpeedY()) * factor;
    }
}

std::string Motion::toString()
{
    std::string desc = "Motion: speed=(" + std::to_string(avgSpeed[0]) + ", " + std::to_string(avgSpeed[1]) + 
            ") accel=(" + std::to_string(avgAccel[0]) + ", " + std::to_string(avgAccel[1]) + ") \n";
            
    for (Move2D& oMove : listMoves)
    {
        desc += oMove.toString();
    }

    return desc;
}

}
							 