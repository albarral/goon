#ifndef __GOON_DATA_VNATURE_H
#define __GOON_DATA_VNATURE_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
namespace goon 
{
 class vNature
{     
 private:
        int type;       // text, ...
        int clazz;
        int model;
        int complexity;              

 public:
//     vNature ();
//     ~vNature();

    int getType() {return type;}
    void setType(int value) {type=value;}    

    int getClass() {return clazz;}
    void setClass(int value) {clazz=value;}    

    int getModel() {return model;}
    void setModel(int value) {model=value;}    

    int getComplexity() {return complexity;}
    void setComplexity(int value) {complexity=value;}    
};  
}  
#endif
