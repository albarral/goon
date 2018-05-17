/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include "goon/features/structure/Structure.h"

namespace goon
{
// Constructor
Structure::Structure ()
{
}

// copy constructor (needed for mask)    
Structure::Structure(const Structure& oStructure)
{
    // mat is cloned if not empty
    if (!oStructure.matNeighbours.empty())
        matNeighbours = oStructure.matNeighbours.clone(); 
}  

// assignment operator (needed for mask)
Structure& Structure::operator=(const Structure& oStructure)
{
    // mat is cloned if not empty
    if (!oStructure.matNeighbours.empty())
        matNeighbours = oStructure.matNeighbours.clone(); 
    return *this;    
}

void Structure::resize(int numElements)
{
    matNeighbours = cv::Mat::zeros(numElements, numElements, CV_32FC4);
}
							 

std::vector<cv::Vec4f> Structure::getNeighbours(int element)
{
    std::vector<cv::Vec4f> listNeighbours; 

    // check existing element
    if (element < matNeighbours.rows)
    {
        // get element row
        cv::Mat matRow = matNeighbours.row(element);
        // for each neighbour, add it to list	
        for (int j=0; j<matRow.cols; j++)
        {
            listNeighbours.push_back(matRow.at<cv::Vec4f>(j));
        }
    }
    
    // return list
    return listNeighbours;
}


void Structure::setNeighbours(int element, std::vector<cv::Vec4f>& listNeighbours)
{
    // check existing element & neighbours quantity
    if (element < matNeighbours.rows && listNeighbours.size() < matNeighbours.cols)
    {
        // get element row
        cv::Mat matRow = matNeighbours.row(element);
        int j=0;
        // for each neighbour in list, add it to matrix
        for (cv::Vec4f& neighbour : listNeighbours)
        {
            matRow.at<cv::Vec4f>(j) = neighbour;
            j++;
        }
    }
}

void Structure::clearNeighbours(int element)
{
    // check existing element
    if (element < matNeighbours.rows)
    {
        // get element row
        cv::Mat matRow = matNeighbours.row(element);
        matRow = cv::Scalar::all(0);
    }
}

void Structure::clear()
{
    matNeighbours = cv::Scalar::all(0);
}
}
