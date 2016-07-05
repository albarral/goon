#ifndef __GOON_UTILS_TRIGGER_H
#define __GOON_UTILS_TRIGGER_H

/***************************************************************************
 *   Copyright (C) 2014 by Migtron Robotics   *
 *   albarral@migtron.com   *
 ***************************************************************************/


namespace goon
{
// This class monitors a physical 1D variable (area, age, angular speed ...) triggering a response whenever it experiments a specified change (increase).
class Trigger
{
private:
    float CHANGE_FACTOR;     // amount of proportional change that triggers the response
    int MIN_CHANGE;             // minimum absolute change required to trigger the response
    int trigger_value;             // next variable's value that will trigger the response 

public:

    Trigger();
    ~Trigger();

    void setParams (float change_factor, int min_change);

    // Resets the trigger.
    void reset();
    
    // Checks if the monitored variable has changed enough (the specified factor). 
    // If so, true is returned, otherwise false is returned.
    bool check(int present_value) {return (present_value > trigger_value);};

    // The next trigger value is updated taking into account the specified present value.
    void update(int present_value);
};
}
		  	    		    
#endif
