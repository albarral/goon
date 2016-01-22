#ifndef __GOON_DATA_IDENTITY_H
#define __GOON_DATA_IDENTITY_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/

#include <string>

#include "goon/data/aux/vNature.h"

namespace goon 
{
// This class represents an object's identity.
// It holds info about the object's existence: Identity_type (class or instance), nature and name.
class Identity 
{
public:        
    enum eTypes
    {
     eIDENT_INSTANCE, 
     eIDENT_CLASS
    };	

protected:
    int identity_type;
    vNature nature;
    std::string name;   
    
public:
    Identity();
     //~Identity();

    int getType() {return identity_type;}        

    bool isInstance() {return (identity_type == eIDENT_INSTANCE);}
    bool isClass() {return (identity_type == eIDENT_CLASS);}    
    void setClass() {identity_type = eIDENT_CLASS;}

    vNature& getNature() {return nature;};     

    std::string getName() {return name;}    
    void setName (std::string aname) {name = aname;};                    
 };
}
#endif
