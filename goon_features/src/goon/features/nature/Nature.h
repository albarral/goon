#ifndef __GOON_FEATURES_NATURE_H
#define __GOON_FEATURES_NATURE_H

/***************************************************************************
 *   Copyright (C) 2018 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/
	
#include <string>

 namespace goon
{
class Nature
{
 private:
     int category; 
     int type;
     int ID;
     std::string name;

 public:
     Nature();
     //~Nature();
     
     int getCategory() {return category;};
     int getType() {return type;};
     int getID() {return ID;};
     std::string getName() {return name;};

     void setCategory(int value) {category = value;};
     void setType(int value) {type = value;};
     void setID(int value) {ID = value;};
     void setName(std::string value) {name = value;};

     std::string toString();         
};  
}
  
#endif
