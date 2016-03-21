/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <chrono>

#include "goon/features/motion/Motion.h"

namespace goon 
{
namespace features
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

void Motion::update(features::Move2D& oTransMove)
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
    features::Move2D lastMove = listMoves.back();
    features::Move2D firstMove = listMoves.front();
    
    std::chrono::duration<int, std::milli> motionInterval = std::chrono::duration_cast<std::chrono::milliseconds>(lastMove.getTimeStamp() - firstMove.getTimeStamp());
    int motionMillis = motionInterval.count();        

    if (motionMillis > 0)
    {
        avgSpeed[0] = (lastMove.getValueX() - firstMove.getValueX()) / motionMillis;
        avgSpeed[1] = (lastMove.getValueY() - firstMove.getValueY()) / motionMillis;
        avgAccel[0] = (lastMove.getSpeedX() - firstMove.getSpeedX()) / motionMillis;
        avgAccel[1] = (lastMove.getSpeedY() - firstMove.getSpeedY()) / motionMillis;
    }
}

}
}
							 