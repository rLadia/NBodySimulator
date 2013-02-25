#ifndef LADIA_CSS342_NBODYSIMULATION_H
#define LADIA_CSS342_NBODYSIMULATION_H

#include <vector>
#include <list>
#include <cassert>
#include <limits>
#include <algorithm>

#include "color.h"
#include "collision.h"
#include "gravity.h"
#include "simulatedbody.h"

//accepts a groups of spheres and calculates when they collide
//will destroy the smaller sphere when it collides

static const double TIMEINTERVAL = 0.1;
static const int GRAVITY = 10;

class NBodySimulation {
public:
  enum CollisionType {
    kCollision, // collided with another sphere
    kBlackHole, //collided with the black hole
    kBoundary, //collided with the boundary
  };

  //Contains user accessible information about a collision
  struct Record {
    int index; //the index of the sphere that collided
    int time; //the time of the collision
    CollisionType collision; // the type of collision that occured
  };

  //adds a sphere to the internal list of bodies to be simulated
  void addBody(Color::Color, const Vector3 &, int, const Vector3 &);
  
  //adds a black hole to the bodies to be simulated
  void addBlackHole(const Vector3 &, int);

  //will remove bodies as they collide
  //stop when bodies are stable?
  //void simulate(); //advance the simulation until no more bodies exist

  //return: vector containing the information about all of the collisions
  //  that have occurred so far
  std::vector<Record> getSimulationResults();

  // runs the simulation until all spheres are dead
  void runSimulation(); 

  NBodySimulation(unsigned int); //boundary size

private:
  //associates a body with an index value and color
  struct ManagedBody {
    int index;
    SimulatedBody body;
    Color::Color color;
  };
  
  //contains information about the time and participants in a collision
  //Natural sorting will order the elements by the time of collision
  struct Collision {
    double time;
    const ManagedBody* left;
    const ManagedBody* right;

    bool operator< (const Collision &rhs) {
      return time < rhs.time;
    }
  };

  unsigned int boundary_; //the length of the bounding cube
  unsigned int index_; //current sphere index
  double time_; //current time of the simulation

  //contains the list of eliminations caused by collisions
  std::vector<Record> records_;
  
  //contains all possible collisions made by the spheres
  std::list<Collision> collisions_; 

  //contains the list of bodies to be simulated
  std::list<ManagedBody> bodies_;
  std::list<SimulatedBody> black_holes_;
  std::list<ManagedBody> massless_bodies_;

  typedef std::list<NBodySimulation::ManagedBody>::iterator ManagedBodyIterator;
  typedef std::list<SimulatedBody>::iterator SimulatedBodyIterator;
  typedef std::list<MovingSphere>::iterator MasslessBodyIterator;

  typedef Color::Color Color;

  void calculateForcesFromSpheres();
  void calculateForcesFromBlackHoles();

  //updates the acceleration of each body 
  void updateForce(SimulatedBody &, SimulatedBody &);

  // sets all of the forces in the bodies to 0
  void resetForces();

  const ManagedBody* determineResult(const ManagedBody &, const ManagedBody &);

  //returns the sphere with the smaller radius
  //if the radii are the same, it returns the first argument
  static const ManagedBody* smallerSphere(const ManagedBody*, const ManagedBody*);

  //Iterates through the list and returns the smallest, positive value
  static double smallestTime(const std::vector<double>&);

  void advance(double); // advances the simulation by the time period given

  //Calculates the collision times between the two spheres and adds the
  //soonest one. If the second argument is null, it calculates the time it
  //takes for the sphere to collide with the boundary and adds that collision.
  //
  //pre: sphere1 is non-null, sphere2 is null if the sphere is colliding with 
  //  the boundary
  //post: collisions_ appended with collisions from two input spheres
  void calculateCollision(const ManagedBody*, const ManagedBody*);

  //Compares each sphere with every other sphere and the boundary. All 
  //collisions detected by these comparisions will be added to collisions_.
  //
  //post: collisions_ appended with all possible collisions made between 
  //  spheres and the boundary
  void findAllOverlaps();

  //Iterates through the list of collisions and records the eliminations that 
  //result. Once a sphere has been eliminated, this function removes all future
  //collisions that involved that sphere.
  //
  //post: records_ contains all of the eliminations made by the simulation. 
  //  collision_ is empty
  void recordEliminations();
  
  //Returns a vector containing the times the sphere will collide with each
  //of the six planes of the boundary cube. If one dimension of the sphere 
  //is stationary, there will be no collisions for that dimension. Boundary
  //collisions at t=0 are not added.
  std::vector<double> boundaryCollisionTimes(const MovingSphere &);

  //Adds the elimination record to the list of records. This function will only
  //add a record for the smaller sphere involved in the collision with the
  //boundary being larger than all spheres.
  //
  //return: the sphere added to the list of elimination records
  //post: records_ appended with the time, index and type of collision
  const ManagedBody* addEliminationRecord(const Collision &);

  //do not make a copy of this class
  NBodySimulation(const NBodySimulation &);
  NBodySimulation& operator=(const NBodySimulation &);
};

#endif
