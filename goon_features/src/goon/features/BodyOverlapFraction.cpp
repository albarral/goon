/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/BodyOverlapFraction.h"

namespace goon 
{
int BodyOverlapFraction::computeOverlaps(std::list<Body>& listBodies1, std::list<Body>& listBodies2)
{
    // create overlap matrix (bodies 1 x bodies 2)
    matOverlaps = cv::Mat::zeros(listBodies1.size(), listBodies2.size(), CV_32SC1);    

    int numOverlaps = 0;
    int row = 0, col = 0;    
    int overlap;
    int fraction; // percentage
    
    // walk list 1 (rows)
    for (Body& oBody1 : listBodies1)
    {               
        cv::Mat matRow = matOverlaps.row(row);                
        // walk list 2 (columns)
        for (Body& oBody2 : listBodies2)
        {               
            // compute overlapped area
            overlap = oBody1.computeOverlap(oBody2);
            // if positive, store it
            if (overlap > 0)
            {
                // protect against zero division
                if (oBody1.getMass() > 0)
                    fraction = overlap*100 / oBody1.getMass();
                else
                    fraction = 1000;

                matRow.at<int>(col) = fraction;
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
}
							 