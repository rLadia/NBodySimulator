/*
Interface for initializing and retreiving updates from the simulation model.

The user gives the model information about the initial conditions and time
elapsed. (later on, any additional input that comes from the user). The model 
calculates the effect that the initial conditions have on the model and 
returns the data in a parseable fashion.

References the rules for determining how the objects in the model interact 
with each other.
*/

#include <vector>
#include <list>
#include "ModelObject.h"

#ifndef LADIA_NBODYSIMULATOR_MODEL_H
#define LADIA_NBODYSIMULATOR_MODEL_H

class Model
{
public:
  typedef std::vector<ModelObject> ObjectList;

  Model();

  // updates state of model after the given time interval has passed
  // The objects can have their position, velocity or force modified 
  // and may be removed from the list
  void Update(ObjectList &, double);

private:
  // calculates the gravitational forces between each object
  // and adds it to their force property
  void UpdateGravitationalForces(ObjectList &);

  // Removes objects that are overlapping from the list
  void HandleOverlaps(ObjectList &);
};

#endif
