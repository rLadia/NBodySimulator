#include "Model.h"
#include "nbodysimulator.h"
#include <iostream>
#include <algorithm>
#include "overlap.h"

Model::Model()
{}

void Model::Update(ObjectList &objects, const double time)
{
  UpdateGravitationalForces(objects, time);
  HandleOverlaps(objects);
}

void Model::UpdateGravitationalForces(ObjectList &objects, const double time)
{
  NBodySimulator simulator;
  simulator.Simulate(objects, time);
}

void Model::HandleOverlaps(ObjectList &objects)
{
  ObjectList::iterator i = objects.begin();

  while(i != objects.end()) {
    ObjectList::iterator j = i;
    j ++; // do not compare to self
    while(j != objects.end()) {
      if(IsOverlapping(*i, *j)) { // remove the objects from the list
        objects.erase(j);
        i = objects.erase(i);
        break; // inner loop is complete
      } else
        ++i;
    }
  };
}

bool Model::IsOverlapping(ModelObject &left, ModelObject &right)
{
  Shape::Sphere circle_left = { left.position(), left.radius() };
  Shape::Sphere circle_right = { right.position(), right.radius() };

  return (Overlap::IsOverlapping(circle_left, circle_right));
}
