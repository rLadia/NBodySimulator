#include "nbodysimulator.h"
#include <boost/foreach.hpp>

typedef boost::shared_ptr<SimulatedBody> BodyPtr;

NBodySimulator::NBodySimulator(int boundary) 
  : boundary_(boundary)
{}

// adds a body to be simulated
void NBodySimulator::SetBodyList(const std::list<BodyPtr> &bodies)
{
  bodies_ = bodies;
}

//*TODO* add check for stable orbits
// run until all spheres have collided
void NBodySimulator::RunSimulation(const double timeinterval)
{
  updateAllForces();

  typedef boost::shared_ptr<SimulatedBody> Body;
  BOOST_FOREACH(Body b, bodies_) {
    b->advance(timeinterval);
  }
}

// Updates the instantaneous force exerted on all of the simulated bodies
void NBodySimulator::updateAllForces()
{
  resetForces(); //start from 0
  calculateForcesBetweenBodies();
}

// set the forces of each simulated body to 0
void NBodySimulator::resetForces() 
{
  for(BodyList::iterator i = bodies_.begin(); i != bodies_.end(); ++i)
    (*i)->setForce(Vector3(0,0,0));
}


// Calculates the instantaneous forces exerted on the simulated bodies
// by each other simulated body
void NBodySimulator::calculateForcesBetweenBodies() 
{
  BodyList::iterator i = bodies_.begin();

  for(i; i != bodies_.end(); ++i) {
    BodyList::iterator j = i; //not necessary to start at beginning

    // bodies do not apply a force on themselves
    for(j++; j != bodies_.end(); ++j) {
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
