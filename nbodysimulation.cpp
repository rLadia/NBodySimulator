#include "nbodysimulation.h"

typedef NBodySimulation::Record Record;

NBodySimulation::NBodySimulation(unsigned int boundary) 
  : index_(1), boundary_(boundary), time_(0)
{}

//appends the internal list of spheres with the given attributes of a sphere
void NBodySimulation::addBody(Color::Color color, const Vector3& center,
  int radius, const Vector3& velocity)
{
  SimulatedBody body = SimulatedBody(color, center, radius, velocity);
  IndexedSphere indexed_body = { index_, body };
  
  if(color == Color::Color::kBlack)
    black_bodies_.push_back(indexed_body);
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

void NBodySimulation::advance(double time) {
  //time_ += time;
  //calculate force on each sphere
  //modify velocity on each sphere
  //
}

/*
//Returns a vector of records detailing how and when the spheres collided
std::vector<NBodySimulation::Record> NBodySimulation::calculateEliminations()
{
  records_.clear();
  calculateAllCollisions();
  recordEliminations();
  return records_;
}

//Iterates through list of all collisions and records only the ones that result
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

//n^2 traversal creating complete list of all possible collisions
void NBodySimulation::calculateAllCollisions()
{
  if(bodies_.size() <= 0) //no spheres to check collisions with
    return;
  typedef std::list<NBodySimulation::IndexedSphere*>::iterator Iter;

  Iter i = bodies_.begin();
  do {
    //add the collision with the boundary
    calculateCollision(*i, NULL);

    Iter j = i; //not necessary to start at beginning

    //Spheres cannot collide with themselves
    for(j++; j != bodies_.end(); ++j) {
      calculateCollision(*i, *j); //add collision between the two spheres
    }
    i++;
  } while(i != bodies_.end());
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