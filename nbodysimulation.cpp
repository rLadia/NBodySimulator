#include "nbodysimulation.h"

typedef NBodySimulation::Record Record;

NBodySimulation::NBodySimulation(unsigned int boundary) 
  : index_(1), boundary_(boundary), time_(0)
{}

//appends the internal list of spheres with the given attributes of a sphere
void NBodySimulation::addBody(Color color, const Vector3& center,
  int radius, const Vector3& velocity)
{
  // initializes with acceleration of 0 and mass equal to radius
  SimulatedBody body = 
    SimulatedBody(center, radius, velocity, Vector3(0,0,0), radius);

  ManagedBody indexed_body = { index_, body, color };
  
  if(color == Color::kBlack)
    freemoving_bodies_.push_back(indexed_body);
  else
     bodies_.push_back(indexed_body);

  index_++;
}

//assigns the properties to the black hole and adds it to the list of black holes
void NBodySimulation::addBlackHole(const Vector3& center, int mass)
{
  SimulatedBody black_hole;
  black_hole.setCenter(center);
  black_hole.setMass(mass);
  black_holes_.push_back(black_hole);
}

//Returns a vector of records detailing how and when the bodies collided
std::vector<NBodySimulation::Record> NBodySimulation::getSimulationResults()
{
  return records_;
}

//*TODO* add check for stable orbits
// run until all spheres have collided
void NBodySimulation::runSimulation()
{
  while(! bodies_.empty() || ! freemoving_bodies_.empty()) { 
    findAllOverlaps();
    updateAllForces();
    advance(TIMEINTERVAL);
  }
}

// calculates 
void NBodySimulation::updateAllForces()
{
  resetForces(); //start from 0
  calculateForcesFromBodies();
  calculateForcesFromFreeMovingBodies();
  calculateForcesFromBlackHoles();
}

// calculates the forces for the current frame and advances the spheres by the 
// given time interval
void NBodySimulation::advance(double time) {
  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i) {
    i->body.advance(time);
  }
  for(ManagedBodyIterator i = freemoving_bodies_.begin(); i != freemoving_bodies_.end(); ++i) {
    i->body.advance(time);
  }

  time_ += time;
}

//set the forces of each body to 0
void NBodySimulation::resetForces() 
{
  typedef std::list<NBodySimulation::ManagedBody>::iterator ManagedBodyIterator;
  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i)
    i->body.setForce(Vector3(0,0,0));
}

void NBodySimulation::calculateForcesFromFreeMovingBodies()
{
  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i) {
    for(ManagedBodyIterator j = freemoving_bodies_.begin(); j != freemoving_bodies_.end(); ++j) {
      updateForce(i->body, j->body);
      j->body.setForce(Vector3(0,0,0)); //massless bodies not affected by mass
    }
  }
}

//n^2 iteration calculating and applying the forc
void NBodySimulation::calculateForcesFromBodies() 
{
  ManagedBodyIterator i = bodies_.begin();
  while(i != bodies_.end()) {
    ManagedBodyIterator j = i; //not necessary to start at beginning

    //bodies do apply a force on themselves
    for(j++; j != bodies_.end(); ++j) {
      updateForce(i->body, j->body);
    }
    i++;
  };
}

void NBodySimulation::calculateForcesFromBlackHoles()
{
  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i) {
    for(SimulatedBodyIterator j = black_holes_.begin(); j != black_holes_.end(); ++j)
      updateForce(i->body, *j);
  }
}

void NBodySimulation::updateForce(SimulatedBody &b1, SimulatedBody &b2)
{
  Gravity::PointMass m1 = { b1.getMass(), b1.getCenter() };
  Gravity::PointMass m2 = { b2.getMass(), b2.getCenter() };

  Vector3 force = Gravity::force(m1, m2, GRAVITY);
  b1.setForce(b1.getForce() + force);
  b2.setForce(b2.getForce() + force * -1);
}

//*TODO* refactor this huge, monolithic function
//n^2 traversal creating complete list of all possible collisions
void NBodySimulation::findAllOverlaps()
{
  if(bodies_.size() <= 0 && freemoving_bodies_.size() <= 0) //no spheres to check collisions with
    return;

  //check overlap of bodies with black holes
  ManagedBodyIterator i = bodies_.begin();
  while(i != bodies_.end()) {
    for(SimulatedBodyIterator j = black_holes_.begin(); j != black_holes_.end(); ++j) {
      if(COLLISION::isOverlapping(i->body, j->getCenter())) {
        recordEvent(*i, time_, CollisionType::kBlackHole);
        i = bodies_.erase(i); //erase body from existence
      } else {
        ++i;
      }
    }
  };

  i = bodies_.begin();
  
  //check overlap between bodies with other bodies
  while(i != bodies_.end()) {
    ManagedBodyIterator j = i; //not necessary to start at beginning
    ++j; //bodies do not collide with themselves

    bool eraseI = false;
    while(j != bodies_.end()) {
      if(COLLISION::isOverlapping(i->body, j->body)) { //overlap found
        if(i->body.getRadius() > j->body.getRadius()) { // j is smaller
          recordEvent(*j, time_, CollisionType::kCollision);
          j = bodies_.erase(j);
        } else {
          recordEvent(*i, time_, CollisionType::kCollision);
          i = bodies_.erase(i);
          eraseI = true;
          break; // do not compare i with rest of values
        }
      }
      else
        ++j;
    };

    if(!eraseI) { //check against massless bodies
      for(ManagedBodyIterator k = freemoving_bodies_.begin(); k != freemoving_bodies_.end(); ++k) {
        if(COLLISION::isOverlapping(i->body, k->body)) {
          recordEvent(*i, time_, CollisionType::kCollision);
          i = bodies_.erase(i);
          eraseI = true;
          break; // do not compare i with rest of the massless bodies
        }
      }
    }

    if(!eraseI) // do not double increment
      i++;
  };

  // check collision with boundary
  i = bodies_.begin();
  while(i != bodies_.end()) {
    if(isOverlappingBoundary(i->body)) {
      recordEvent(*i, time_, CollisionType::kBoundary);
      isOverlappingBoundary(i->body);
      i = bodies_.erase(i);
    } else
      ++i;
  };

  i = freemoving_bodies_.begin();
  while(i != freemoving_bodies_.end()) {
    if(isOverlappingBoundary(i->body)) {
      recordEvent(*i, time_, CollisionType::kBoundary);
      i = freemoving_bodies_.erase(i);
    } else
      ++i;
  };
}

bool NBodySimulation::isOverlappingBoundary(const Sphere &sphere)
{
  Vector3 center = sphere.getCenter();
  int radius = sphere.getRadius();

  for(int i = 0; i < 3; ++i) {
    if(center[i] + radius > boundary_ || center[i] - radius < 0)
      return true;
  }
  return false;
}

void NBodySimulation::recordEvent(
  const ManagedBody &body, double time, NBodySimulation::CollisionType type)
{
  Record record = { body.index, body.color, time, type };
  records_.push_back(record);
}