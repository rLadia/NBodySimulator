#include "nbodysimulator.h"
#include "foreach.hpp"

typedef SimulatedBody* BodyPtr;

NBodySimulator::NBodySimulator(const double time_interval) 
  : time_interval_(time_interval)
{}

NBodySimulator::NBodySimulator(const double time_interval) 
  : time_interval_(kDefaultTimeInterval)
{}

//*TODO* add check for stable orbits
void NBodySimulator::Simulate(BodyList* bodies, const double time_simulated)
{
  double elapsed;
  for(elapsed = 0; 
    elapsed <= time_simulated - time_interval_; 
    elapsed += time_interval_) {

    updateAllForces(*bodies);

    BOOST_FOREACH(BodyPtr b, bodies) {
      b->advance(time_interval_);
    }
  }

  if(time_simulated >= 0) {
    updateAllForces(*bodies);

    BOOST_FOREACH(BodyPtr b, bodies) {
      b->advance(elapsed - time_interval_); // simulate the remaining time
    }
  }
}

// Updates the instantaneous force exerted on all of the simulated bodies
void NBodySimulator::updateAllForces(BodyList &bodies)
{
  resetForces(bodies); //start from 0
  calculateForcesBetweenBodies(bodies);
}

// set the forces of each simulated body to 0
void NBodySimulator::resetForces(BodyList &bodies) 
{
  for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i)
    (*i)->setForce(Vector3(0,0,0));
}


// Calculates the instantaneous forces exerted on the simulated bodies
// by each other simulated body
void NBodySimulator::calculateForcesBetweenBodies(BodyList &bodies) 
{
  BodyList::iterator i = bodies.begin();

  for(i; i != bodies.end(); ++i) {
    BodyList::iterator j = i; //not necessary to start at beginning

    // bodies do not apply a force on themselves
    for(j++; j != bodies.end(); ++j) {
      addForcesBetween(**i, **j);
    }
  };
}


// Adds the force exerted on each body to each body's net force 
void NBodySimulator::addForcesBetween(SimulatedBody &b1, SimulatedBody &b2)
{
  Gravity::PointMass m1 = { b1.getMass(), b1.getCenter() };
  Gravity::PointMass m2 = { b2.getMass(), b2.getCenter() };

  Vector3 force = Gravity::force(m1, m2, kGravity);
  b1.setForce(b1.getForce() + force);
  b2.setForce(b2.getForce() + force * -1);
}
