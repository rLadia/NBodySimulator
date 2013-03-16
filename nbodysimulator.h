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

static const double kTimeInterval = .01;
static const int kGravity = 10;

// Simulates the motion of 3d bodies through space
class NBodySimulator {
public:
  typedef SimulatedBody* Body;
  typedef std::list<Body> BodyList;

  void SetBodyList(const BodyList &);

  // Runs the simulation for the time period given
  // sphere. Every time a body collides, a record will be added that can be
  // accessed by calling getSimulationResults()
  void RunSimulation(const double); 

  NBodySimulator(int); //boundary size

private:

  unsigned int boundary_; //the length of the bounding cube

  //contains the list of bodies to be simulated
  BodyList bodies_;
  
  // Sets the net force of each simulated body to 0
  void resetForces();

  // Updates the net instantaneous force exerted on each simulated body
  // There are gravitational forces acting between each body and from
  // black holes. The black spheres are not affected by gravity.
  void updateAllForces();

  // Calculates the instantaneous forces exerted on the simulated bodies
  // from each other body and from the black hole
  void calculateForcesBetweenBodies();

  // Adds the gravitational force between each body to each body's net force
  void addForcesBetween(SimulatedBody &, SimulatedBody &);
  
  // Advances the simulation by the time period given
  // Each body will move according to its current velocity and the net force
  void advance(const double); 
};

#endif
