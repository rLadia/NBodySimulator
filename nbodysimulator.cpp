#include "nbodysimulator.h"
#include <boost/foreach.hpp>

typedef NBodySimulator::Record Record;
typedef boost::shared_ptr<SimulatedBody> BodyPtr;

NBodySimulator::NBodySimulator(int boundary) 
  : index_(1), boundary_(boundary), time_(0)
{}

// adds a body to be simulated
void NBodySimulator::SetBodyList(const std::list<BodyPtr> &bodies)
{
  // initializes with acceleration of 0 and mass equal to radius
  BOOST_FOREACH(BodyPtr b, bodies) {
    SimulatedBody body = SimulatedBody(
      b->getCenter(), 
      b->getRadius(), 
      b->getVelocity(), 
      Vector3(0,0,0),   // initial force set to 0
      b->getRadius()
    );

    ManagedBody indexed_body = { index_, body, Color::kBlue, false };
    bodies_.push_back(indexed_body);
    index_++;
  }
}

//Returns a vector of records detailing how and when the bodies collided
std::vector<NBodySimulator::Record> NBodySimulator::getSimulationResults()
{
  return records_;
}

//*TODO* add check for stable orbits
// run until all spheres have collided
void NBodySimulator::RunSimulation(const double timeinterval)
{
  updateAllForces();
  advance(timeinterval);
  recordAndMarkCollisions();
}
// removes all simulated bodies and
// resets simulation to initial state
void NBodySimulator::reset()
{
  bodies_.clear();
  black_holes_.clear();
  time_ = 0;
  index_ = 1;
}

// calculates the forces for the current frame and advances the spheres by the 
// given time interval
void NBodySimulator::advance(const double time) {
  BOOST_FOREACH(ManagedBody &b, bodies_) {
    b.body.advance(time);
  }
  time_ += time;
}

// Updates the instantaneous force exerted on all of the simulated bodies
void NBodySimulator::updateAllForces()
{
  resetForces(); //start from 0
  calculateForcesFromBodies();
}

// set the forces of each simulated body to 0
void NBodySimulator::resetForces() 
{
  typedef std::list<NBodySimulator::ManagedBody>::iterator ManagedBodyIterator;
  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i)
    i->body.setForce(Vector3(0,0,0));
}


// Calculates the instantaneous forces exerted on the simulated bodies
// by each other simulated body
void NBodySimulator::calculateForcesFromBodies() 
{
  ManagedBodyIterator i = bodies_.begin();
  while(i != bodies_.end()) {
    ManagedBodyIterator j = i; //not necessary to start at beginning

    //bodies do apply a force on themselves
    for(j++; j != bodies_.end(); ++j) {
      addForcesBetween(i->body, j->body);
    }
    i++;
  };
}

// Calculates the instantaneous forces exerted on the simulated bodies
// by the black holes
void NBodySimulator::calculateForcesFromBlackHoles()
{
  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i) {
    for(SimulatedBodyIterator j = black_holes_.begin(); j != black_holes_.end(); ++j)
      addForcesBetween(i->body, *j);
  }
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

// handles collisions for body-body, body-blackhole and body-boundary
void NBodySimulator::recordAndMarkCollisions()
{
  if(bodies_.size() <= 0) //no spheres to check collisions with
    return;

  // check if bodies overlap with black holes
  handleBlackHoleOverlap(bodies_, black_holes_);

  // check if bodies overlap with each other
  handleBodyOverlap();

  // check if bodies overlap with the boundary
  handleBoundaryOverlap(bodies_);
}

void NBodySimulator::handleBodyOverlap()
{
  ManagedBodyIterator i;

  // iterate through list of bodies_
  for(i = bodies_.begin(); i != bodies_.end(); ++i) {
    ManagedBodyIterator j = i; // Iterator through rest of bodies_

    for(++j; j != bodies_.end(); ++j) { // not necessary to compare to itself
      if(i->isDead || j->isDead) { // do not check dead spheres
        // do nothing
      } else if(COLLISION::isOverlapping(i->body, j->body)) { //overlap found

        // remove the smaller sphere
        const ManagedBodyIterator* removeThis = toBeRemoved(&i, &j);
        if(*removeThis == i) {
          recordAndMarkForDeletion(*i, kCollision);
          break; // do not compare i with rest of the bodies
        } else if (*removeThis == j) {
          recordAndMarkForDeletion(*j, kCollision);
        }
      }
    }
  } // so much nesting!
}

const NBodySimulator::ManagedBodyIterator* NBodySimulator::toBeRemoved(
  const ManagedBodyIterator* left, const ManagedBodyIterator* right)
{
  // black spheres do not interact with each other
  if((*left)->color == Color::kBlack && (*right)->color == Color::kBlack)
    return NULL; 

  // black spheres win all other interactions
  if((*left)->color == Color::kBlack)
    return right;
  if((*right)->color == Color::kBlack)
    return left;

  // the smaller sphere will be removed
  return 
    (*left)->body.getRadius() <= (*right)->body.getRadius() ? left : right;
}

void NBodySimulator::removeDeadBodies()
{
  ManagedBodyIterator i = bodies_.begin();

  // iterate through list of bodies
  while(i != bodies_.end()) {
    if(i->isDead)
      i = bodies_.erase(i);
    else // do not double increment
      ++i;
  };
}

void NBodySimulator::recordAndMarkForDeletion(
  ManagedBody &body, NBodySimulator::CollisionType collsionType)
{
  recordEvent(body, time_, collsionType);
  body.isDead = true;
}

// if any of the bodies collided with a black hole
// the event is recorded and the body is removed from the list
void NBodySimulator::handleBlackHoleOverlap(
  std::list<ManagedBody> &bodies, const std::list<SimulatedBody> & blackholes)
{
  ManagedBodyIterator i; // iterator through list of spheres

  // iterator through list of black holes
  std::list<SimulatedBody>::const_iterator j; 

  for(i = bodies_.begin(); i != bodies_.end(); ++i) {
    for(j = blackholes.begin(); j != blackholes.end(); ++j) { 
      if(COLLISION::isOverlapping(i->body, j->getCenter())) { // overlap found
        recordAndMarkForDeletion(*i, kBlackHole);
      }
    }
  }
}

// if any of the bodies collided with the boundary
// the event is recorded and the body is removed from the simulation
void NBodySimulator::handleBoundaryOverlap(std::list<ManagedBody> &bodies)
{
  ManagedBodyIterator i;

  // iterate through the list of bodies
  for(i = bodies_.begin(); i != bodies_.end(); ++i) {
    if(isOverlappingBoundary(i->body)) { // if overlapping
      recordAndMarkForDeletion(*i, kBoundary);
    }
  };
}

// returns: true if the sphere is overlapping the boundary
bool NBodySimulator::isOverlappingBoundary(const Sphere &sphere)
{
  Vector3 center = sphere.getCenter();
  int radius = sphere.getRadius();

  for(int i = 0; i < 3; ++i) {
    if(center[i] + radius >= boundary_ || center[i] - radius <= 0)
      return true;
  }
  return false;
}

 // Adds the collision event to the list of recorded events
void NBodySimulator::recordEvent(
  const ManagedBody &body, double time, NBodySimulator::CollisionType type)
{
  Record record = { body.index, body.color, time, type };
  records_.push_back(record);
}
