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

  // Contains user accessible information about a collision
  struct Record {
    int index; //the index of the sphere that collided
    Color::Color color;
    double time; //the time of the collision
    CollisionType collision; // the type of collision that occured
  };

  // adds a sphere to the internal list of bodies to be simulated
  void addBody(Color::Color, const Vector3 &, int, const Vector3 &);
  
  // adds a black hole to the bodies to be simulated
  void addBlackHole(const Vector3 &, int);

  //return: vector containing the information about all of the collisions
  //  that have occurred so far
  std::vector<Record> getSimulationResults();

  // runs the simulation until no bodies exist
  // *TODO* add check for stable orbits
  void runSimulation(); 

  NBodySimulation(unsigned int); //boundary size

private:

  //associates a body with an index value and color
  struct ManagedBody {
    int index;
    SimulatedBody body;
    Color::Color color;
  };

  unsigned int boundary_; //the length of the bounding cube
  unsigned int index_; //current sphere index
  double time_; //current time of the simulation

  // contains the list of eliminations caused by collisions
  std::vector<Record> records_;

  //contains the list of bodies to be simulated
  std::list<ManagedBody> bodies_;
  std::list<SimulatedBody> black_holes_;
  std::list<ManagedBody> freemoving_bodies_;

  typedef std::list<NBodySimulation::ManagedBody>::iterator ManagedBodyIterator;
  typedef std::list<SimulatedBody>::iterator SimulatedBodyIterator;

  typedef Color::Color Color;

  void findAllOverlaps();
  
  // Updates the instantaneous force acting upon all of the simulated bodies
  void updateAllForces();

  // sets the net force of the simulated bodies to 0
  void resetForces();

  // Calculates the instantaneous forces exerted on the simulated bodies
  // by each other body, by the free moving bodies, and by the black holes
  void calculateForcesFromBodies();
  void calculateForcesFromFreeMovingBodies();
  void calculateForcesFromBlackHoles();

  // Adds the force exerted on each body to each body's net force 
  void updateForce(SimulatedBody &, SimulatedBody &);
  
  // returns: true if the sphere is overlapping the boundary
  bool isOverlappingBoundary(const Sphere &);
  
  void removeSmallerBody(ManagedBodyIterator, ManagedBodyIterator);

  // advances the simulation by the time period given
  void advance(double); 

  // Adds the collision event to the list of recorded events
  void recordEvent(const ManagedBody&, double, CollisionType);

  

  // do not make a copy of this class
  NBodySimulation(const NBodySimulation &);
  NBodySimulation& operator=(const NBodySimulation &);
};

#endif
