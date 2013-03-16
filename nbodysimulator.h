#ifndef LADIA_CSS342_NBODYSIMULATOR_H
#define LADIA_CSS342_NBODYSIMULATOR_H

#include <algorithm>
#include <cassert>
#include <list>
#include <vector>

#include "color.h"
#include "collision.h"
#include "gravity.h"
#include "simulatedbody.h"



// Simulates the motion of 3d bodies through space
class NBodySimulator {
public:
  typedef SimulatedBody* Body;
  typedef std::list<Body> BodyList;

  static const double kDefaultTimeInterval;
  static const int kGravity = 10;

  // Simulates the effects of gravity on the given list of spheres over the 
  // given time period.
  void Simulate(BodyList *, const double);

  // time interval used to update forces
  NBodySimulator(const double);
  NBodySimulator();

private:
  double time_interval_;
  
  // Sets the net force of each simulated body to 0
  void resetForces(BodyList &);

  // Updates the net instantaneous force exerted on each simulated body
  // There are gravitational forces acting between each body and from
  // black holes. The black spheres are not affected by gravity.
  void updateAllForces(BodyList &);

  // Calculates the instantaneous forces exerted between each simulated body
  void calculateForcesBetweenBodies(BodyList &);

  // Adds the gravitational force between each body to each body's net force
  void addForcesBetween(SimulatedBody &, SimulatedBody &);
  
  // Advances the simulation by the time period given
  // Each body will move according to its current velocity and the net force
  void advance(const double); 
};

#endif
