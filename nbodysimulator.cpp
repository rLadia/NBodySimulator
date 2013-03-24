#include <cassert>

#include "gravity.h"
#include "nbodysimulator.h"

const double NBodySimulator::kDefaultTimeInterval = 0.01;
const double NBodySimulator::kDefaultGravity = 10.0;

NBodySimulator::NBodySimulator(const double time_interval, const double gravity) 
  : time_interval_(time_interval), gravity_(gravity)
{}

NBodySimulator::NBodySimulator() 
  : time_interval_(kDefaultTimeInterval), gravity_(kDefaultGravity)
{}

void NBodySimulator::Simulate(BodyList &bodies, const double time_simulated)
{
  double elapsed;
  for(elapsed = 0; 
    elapsed <= time_simulated - time_interval_; 
    elapsed += time_interval_) {

    UpdateAllForces(bodies);

    for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i)
      i->Advance(time_interval_);
  }

  // simulates any time remaining
  if(elapsed > time_simulated && time_simulated >= 0) {
    UpdateAllForces(bodies);

    for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i)
      i->Advance(elapsed - time_interval_);
  }
}

// Updates the instantaneous force exerted on all of the simulated bodies
void NBodySimulator::UpdateAllForces(BodyList &bodies)
{
  ResetForces(bodies); //start from 0
  CalculateForcesBetweenBodies(bodies);
}

// set the forces of each simulated body to 0
void NBodySimulator::ResetForces(BodyList &bodies) 
{
  for(BodyList::iterator i = bodies.begin(); i != bodies.end(); ++i)
    i->set_force(Vector3(0,0,0));
}


// Calculates the instantaneous forces exerted on the simulated bodies
// by each other simulated body
void NBodySimulator::CalculateForcesBetweenBodies(BodyList &bodies) 
{
  BodyList::iterator i = bodies.begin();

  for(i; i != bodies.end(); ++i) {
    BodyList::iterator j = i; // not necessary to start at beginning
    j ++; // bodies do not apply a force on themselves
    for(; j != bodies.end(); ++j) {
      AddForcesBetween(*i, *j);
    }
  };
}


// Adds the force exerted on each body to each body's net force 
void NBodySimulator::AddForcesBetween(ModelObject &b1, ModelObject &b2)
{
  Gravity::PointMass m1 = { b1.mass(), b1.position() };
  Gravity::PointMass m2 = { b2.mass(), b2.position() };

  Vector3 force = Gravity::force(m1, m2, gravity_);
  b1.set_force(b1.force() + force);
  b2.set_force(b2.force() + force * -1);
}
