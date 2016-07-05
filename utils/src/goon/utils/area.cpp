/***************************************************************************
 *   Copyright (C) 2013 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/utils/area.h"


namespace goon
{
float Area::getWindowOverlap(CvRect* window1, CvRect* window2)
{
    int w1_xend, w2_xend, w1_yend, w2_yend;
    int xleft, xright, ytop, ybottom, w, h;
    float overlap;

    // get window ends
    w1_xend = window1->x + window1->width;
    w2_xend = window2->x + window2->width;
    w1_yend = window1->y + window1->height;
    w2_yend = window2->y + window2->height;

    // obtain the intersection rectangle
    xleft = (window1->x > window2->x ? window1->x : window2->x);
    xright = (w1_xend < w2_xend ? w1_xend : w2_xend);
    ytop = (window1->y > window2->y ? window1->y : window2->y);
    ybottom = (w1_yend < w2_yend ? w1_yend : w2_yend);

    w = xright - xleft;
    h = ybottom - ytop; // y axis faces down

    // if windows overlap compute the intersected fraction of the second window
    if (w > 0 && h >0)
        overlap = (float)(w * h) / (window2->width * window2->height);
    else
        overlap = 0;

    return overlap;
}

}

