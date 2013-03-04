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

static const double TIMEINTERVAL = .01;
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
    Color::Color color;
    double time; //the time of the collision
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
  
  void updateAllForces();
  void calculateForcesFromMasslessBodies();
  void calculateForcesFromBodies();
  void calculateForcesFromBlackHoles();

  
  //updates the force of each body 
  void updateForce(SimulatedBody &, SimulatedBody &);

  // sets all of the forces in the bodies to 0
  void resetForces();

  bool isOverlappingBoundary(const Sphere &);
  void removeSmallerBody(ManagedBodyIterator, ManagedBodyIterator);

  //returns the sphere with the smaller radius
  //if the radii are the same, it returns the first argument
  static const ManagedBody* smallerSphere(const ManagedBody*, const ManagedBody*);

  //Iterates through the list and returns the smallest, positive value
  static double smallestTime(const std::vector<double>&);

  void advance(double); // advances the simulation by the time period given

  //body, time, type
  void recordEvent(const ManagedBody&, double, CollisionType);

  //Compares each sphere with every other sphere and the boundary. All 
  //collisions detected by these comparisions will be added to collisions_.
  //
  //post: collisions_ appended with all possible collisions made between 
  //  spheres and the boundary
  void findAllOverlaps();

  //do not make a copy of this class
  NBodySimulation(const NBodySimulation &);
  NBodySimulation& operator=(const NBodySimulation &);
};

#endif
