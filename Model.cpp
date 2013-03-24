#include "Model.h"
#include "nbodysimulator.h"
#include <iostream>
#include <algorithm>
#include "overlap.h"

const double Model::kTimeInterval = NBodySimulator::kDefaultTimeInterval;

Model::Model()
{}

void Model::Update(
  ObjectList &objects, 
  const double time_elapsed)
{
  Update(objects, time_elapsed, kTimeInterval);
}

void Model::Update(
  ObjectList &objects, 
  const double time_simulated, 
  const double time_interval)
{
  NBodySimulator simulator(time_interval, NBodySimulator::kDefaultGravity);
  simulator.Simulate(objects, time_simulated, &Model::HandleOverlaps);
}

void Model::UpdateGravitationalForces(ObjectList &objects, const double time)
{
  NBodySimulator simulator;
  simulator.Simulate(objects, time);
}

void Model::HandleOverlaps(ObjectList &objects)
{
  if(objects.size() <= 1) // no overlap possible with one item
    return;

  ObjectList::iterator i = objects.begin();

  while(i != objects.end()) {
    bool isErased = false;
    
    ObjectList::iterator j = i;
    j ++; // do not compare to self
    
    while(j != objects.end()) {
      if(IsOverlapping(*i, *j)) { // remove the objects from the list
        objects.erase(j);
        i = objects.erase(i);
        isErased = true;
        break; // inner loop is complete
      } else
        ++j;
    }
    if(!isErased) // do not double increment
      ++i;
  };
}

bool Model::IsOverlapping(ModelObject &left, ModelObject &right)
{
  Shape::Sphere circle_left = { left.position(), left.radius() };
  Shape::Sphere circle_right = { right.position(), right.radius() };

  return (Overlap::IsOverlapping(circle_left, circle_right));
}
