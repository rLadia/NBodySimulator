#ifndef LADIA_CSS342_NBODYSIMULATOR_H
#define LADIA_CSS342_NBODYSIMULATOR_H

#include <vector>
#include "ModelObject.h"

// Simulates the motion of 3d bodies through space
class NBodySimulator {
public:
  typedef ModelObject Body;
  typedef std::vector<Body> BodyList;

  static const double kDefaultTimeInterval;
  static const int kGravity = 10;

  // Simulates the effects of gravity on the given list of spheres over the 
  // given time period
  void Simulate(BodyList &, const double);

  // Calculates the instantaneous forces exerted on each body by every other
  // body and adds that force to the body's force member
  void CalculateForcesBetweenBodies(BodyList &);

  // time interval used to update forces
  NBodySimulator(const double);
  NBodySimulator();

private:
  double time_interval_;
  
  // Sets the net force of each simulated body to 0
  void ResetForces(BodyList &);

  // Updates the net instantaneous force exerted on each simulated body
  // There are gravitational forces acting between each body and from
  // black holes. The black spheres are not affected by gravity.
  void UpdateAllForces(BodyList &);

  // Adds the gravitational force between each body to each body's net force
  void AddForcesBetween(ModelObject &, ModelObject &);
};

#endif
