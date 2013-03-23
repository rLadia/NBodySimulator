/*
Interface for initializing and retreiving updates from the simulation model.

The user gives the model information about the initial conditions and time
elapsed. (later on, any additional input that comes from the user). The model 
calculates the effect that the initial conditions have on the model and 
returns the data in a parseable fashion.


References the rules for determining how the objects in the model interact 
with each other.
*/

#ifndef LADIA_NBODYSIMULATOR_MODEL_H
#define LADIA_NBODYSIMULATOR_MODEL_H

class Model
{
public:
  Model();
private:

};

#endif
