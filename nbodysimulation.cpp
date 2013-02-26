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
    massless_bodies_.push_back(indexed_body);
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

// calculates the forces for the current frame and advances the spheres by the 
// given time interval
void NBodySimulation::advance(double time) {
  
  calculateForcesFromSpheres();
  calculateForcesFromBlackHoles();

  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i) {
    i->body.advance(time);
  }
  for(ManagedBodyIterator i = massless_bodies_.begin(); i != massless_bodies_.end(); ++i) {
    i->body.advance(time);
  }

  time_ += time;
}

//n^2 iteration calculating and applying the forc
void NBodySimulation::calculateForcesFromSpheres() 
{
  if(bodies_.size() <= 0) //no spheres to check collisions with
  return;

  resetForces(); //start from 0

  ManagedBodyIterator i = bodies_.begin();
  do {
    ManagedBodyIterator j = i; //not necessary to start at beginning

    //Spheres do not interact with themselves
    for(j++; j != bodies_.end(); ++j) {
      updateForce(i->body, j->body);
    }
    i++;
  } while(i != bodies_.end());
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

//set all of the forces of each body to 0
void NBodySimulation::resetForces() 
{
  typedef std::list<NBodySimulation::ManagedBody>::iterator ManagedBodyIterator;
  for(ManagedBodyIterator i = bodies_.begin(); i != bodies_.end(); ++i)
    i->body.setForce(Vector3(0,0,0));
}

//Returns a vector of records detailing how and when the bodies collided
std::vector<NBodySimulation::Record> NBodySimulation::getSimulationResults()
{
  return records_;
}

// run until all spheres have collided
void NBodySimulation::runSimulation()
{
  // check collisions
  while(! bodies_.empty() || ! massless_bodies_.empty()) { //or stable orbits
    advance(TIMEINTERVAL);
    findAllOverlaps();
    // remove overlaps
  }
}

void NBodySimulation::recordEvent(
  const ManagedBody &body, int time, NBodySimulation::CollisionType type)
{
  Record record = { body.index, time, type };
  records_.push_back(record);
}

//n^2 traversal creating complete list of all possible collisions
void NBodySimulation::findAllOverlaps()
{
  if(bodies_.size() <= 0) //no spheres to check collisions with
    return;

  std::list<Collision> collisions; 

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
  
  //check collision with other spheres
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
    if(!eraseI) // do not double increment
      i++;
  };

  // check collision with boundary
  i = bodies_.begin();
  while(i != bodies_.end()) {
    if(isOverlappingBoundary(i->body)) {
      recordEvent(*i, time_, CollisionType::kBoundary);
      i = bodies_.erase(i);
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

/*

//ManagedBodyIteratorates through list of all collisions and records only the ones that result
//in eliminations.
void NBodySimulation::recordEliminations()
{
  assert(collisions_.size() > 0); 
  collisions_.sort(); //collisions are dependent on time occured
  std::list<Collision>::iterator i;
  
  do {
    i = collisions_.begin();

    //Only the smaller sphere is destroyed
    const IndexedSphere* destroyedSphere = addEliminationRecord(*i);

    //The rest of the collisions occur in the future. Because the smaller
    //sphere was destroyed, it will no longer have a chance to collide with
    //other spheres.
    while(i != collisions_.end()) {
      if(i->left == destroyedSphere || i->right == destroyedSphere) {
        i = collisions_.erase(i);
      }
      else
        i++;
    };

    //loop until all collisions have been handled
  } while(collisions_.size() > 0);
}

//adds the record to records_ and returns the sphere that was eliminated
const NBodySimulation::IndexedSphere* 
  NBodySimulation::addEliminationRecord(const Collision &c)
{
    const IndexedSphere* destroyedSphere; 
    bool isBoundaryCollision;

    if(c.right == NULL) {//boundary collision
      destroyedSphere = c.left;
      isBoundaryCollision = false;
    } else { //eliminate the smaller sphere
      destroyedSphere = smallerSphere(c.left, c.right);
      isBoundaryCollision = true;
    }

    //record the collision
    records_.push_back(Record(
      destroyedSphere->index,
      static_cast<int>(c.time),
      isBoundaryCollision
    ));

    return destroyedSphere;
}

//It will return the smallest, positive time of collision. If there is only 
//  one possible time of collision, it will return that.
//pre: size of times > 0
double NBodySimulation::smallestTime(const std::vector<double>& times)
{
  assert(times.size() > 0);
 
  std::vector<double>::const_iterator i;
  double smallestTime = std::numeric_limits<double>::max();

  for(i = times.begin(); i != times.end(); ++i) {
    if(*i >= 0 && *i < smallestTime)
      smallestTime = *i;
  }

  return smallestTime;
}

//Calculates collision times and adds soonest value to collisions_
void NBodySimulation::calculateCollision(const IndexedSphere* left, const IndexedSphere* right) 
{
  std::vector<double> times;
  if(right == NULL) {  //colliding with boundary
    times = boundaryCollisionTimes(left->sphere);
  } else {
    times = COLLISION::calculateCollisionTimes(left->sphere, right->sphere);
  }

  if(times.size() > 0) {
    collisions_.push_back(
      Collision(smallestTime(times), left, right)
    );
  }
}

//will not add boundary collisions at t=0
std::vector<double> NBodySimulation::boundaryCollisionTimes(const MovingSphere &sphere)
{
  std::vector<double> times; 
  int radius = sphere.getRadius();
  Vector3 position = sphere.getCenter();
  Vector3 velocity = sphere.getVelocity();

  for(int i = 0; i < 3; ++i) {
    if(velocity[i] != 0) { //stationay spheres will not collide with the boundary
      //calculates time it takes for a sphere to collide with the plane 
      //x,y,z = 0, and x,y,z = boundary_
       times.push_back(static_cast<double>((boundary_ - position[i] - radius))/velocity[i]);
       times.push_back(static_cast<double>((0 - position[i] + radius))/velocity[i]);
    }
  }
  
  return times;
}

//returns the sphere with the smaller radius
const NBodySimulation::IndexedSphere* 
  NBodySimulation::smallerSphere(const IndexedSphere* lhs, const IndexedSphere* rhs)
{
  assert(("Spheres cannot be null.", lhs != NULL && rhs != NULL));
  return lhs->sphere.getRadius() <= rhs->sphere.getRadius() ? lhs : rhs;
}
*/