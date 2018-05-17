/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/BodyOverlap.h"

namespace goon 
{
int BodyOverlap::computeOverlaps(std::list<Body>& listBodies1, std::list<Body>& listBodies2)
{
    // create overlap matrix (bodies 1 x bodies 2)
    matOverlaps = cv::Mat::zeros(listBodies1.size(), listBodies2.size(), CV_32SC1);    

    int numOverlaps = 0;
    int row = 0, col = 0;    
    int overlap;
    // walk list 1 (rows)
    for (Body& oBody1 : listBodies1)
    {               
        cv::Mat matRow = matOverlaps.row(row);                
        // walk list 2 (columns)
        for (Body& oBody2 : listBodies2)
        {               
            // compute bodies overlap
            overlap = oBody1.computeOverlap(oBody2);
            // if positive, store it
            if (overlap > 0)
            {
                matRow.at<int>(col) = overlap;
                numOverlaps++;                
            }
            col++;
        }
        row++;        
    }            
    
    if (numOverlaps > 0)
        computeCorrespondences();
    
    // return number of correspondences
    return listCorrespondences.size();
}

void BodyOverlap::computeCorrespondences()
{    
    double maxVal; 
    cv::Point maxLoc;
    int row, col;
    bool bsearch = true;
    
    // clear correspondences
    listCorrespondences.clear();
    
    // keep searching until no more overlaps exist
    while (bsearch)
    {
        // find maximum overlap
        cv::minMaxLoc(matOverlaps, NULL, &maxVal, NULL, &maxLoc);
        
        // if positive value found
        if (maxVal > 0)
        {
            row = maxLoc.y;   //  list 1
            col = maxLoc.x;    //  list 2  
            
            // add correspondence
            listCorrespondences.push_back(cv::Vec2i(row, col));

            // and clear overlaps with third bodies
            cv::Mat matRow = matOverlaps.row(row);                
            cv::Mat matCol = matOverlaps.col(col);                
            matRow.setTo(0);
            matCol.setTo(0);            
        }                
        // if nothing found, finish search
        else
            bsearch = false;
    }    
}
}
							 