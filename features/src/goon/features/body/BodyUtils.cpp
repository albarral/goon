/***************************************************************************
 *   Copyright (C) 2016 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/body/BodyUtils.h"

namespace goon 
{
namespace features
{     
// Constructor
BodyUtils::BodyUtils ()
{    
}

BodyUtils::~BodyUtils ()
{
}

 // Computes the overlaps between the two lists of Bodies.
 // It leaves the overlap fraction values in matOverlaps, and indicates the filled positions in listOverlaps
void BodyUtils::computeOverlaps(std::vector<Body> listBodies1, std::vector<Body> listBodies2)
{
    listOverlaps.clear();
    
    int rows = listBodies1.size();
    int cols = listBodies2.size();
    
    if (rows > 0 && cols > 0)
    {
        float overlap1, overlap2;
        // reset overlap matrix
        matOverlaps = cv::Mat::zeros(rows, cols, CV_32F);
        
        int n1=0;
        for (Body& oBody1 : listBodies1)
        {
            int n2=0;
            for (Body& oBody2 : listBodies2)
            {
                // if bodies overlap, store overlap fractions and add node to overlaps list
                if (oBody1.checkBodyOverlap(oBody2, overlap1, overlap2))
                {
                    matOverlaps.at<float>(n1,n2) = overlap1;
                    matOverlaps.at<float>(n2,n1) = overlap2;
                    listOverlaps.push_back(std::make_pair(n1,n2));
                }
                n2++;
            }            
            n1++;
        }
    }
}  


}
}
							 