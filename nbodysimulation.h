#ifndef LADIA_CSS342_NBODYSIMULATION_H
#define LADIA_CSS342_NBODYSIMULATION_H

#include <algorithm>
#include <cassert>
#include <list>
#include <vector>

#include "color.h"
#include "collision.h"
#include "gravity.h"
#include "simulatedbody.h"

static const double TIMEINTERVAL = .01;
static const int GRAVITY = 10;

// Simulates the motion of 3d bodies through space
class NBodySimulation {
public:
  enum CollisionType {
    kCollision, // collided with another sphere
    kBlackHole, //collided with the black hole
    kBoundary //collided with the boundary
  };

  // Contains user accessible information about a collision
  struct Record {
    int index; //the index of the sphere that collided
    Color::Color color;
    double time; //the time of the collision
    CollisionType collision; // the type of collision that occured
  };

  // adds a body to be simulated
  void addBody(Color::Color, const Vector3 &, int, const Vector3 &);
  
  // adds a black hole to be simulated
  void addBlackHole(const Vector3 &, int);

  // returns a vector containing the information 
  // about all of the events that have occured
  std::vector<Record> getSimulationResults();

  // runs the simulation until no bodies exist
  // *TODO* add check for stable orbits
  void runSimulation(); 

  // removes all simulated bodies and
  // resets simulation to initial state
  void reset();

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

  typedef std::list<NBodySimulation::ManagedBody>::iterator ManagedBodyIterator;
  typedef std::list<SimulatedBody>::iterator SimulatedBodyIterator;

  typedef Color::Color Color;
  
  // Updates the instantaneous force exerted on all of the simulated bodies
  void updateAllForces();

  // sets the net force of the simulated bodies to 0
  void resetForces();

  // Calculates the instantaneous forces exerted on the simulated bodies
  // by each other body, by the free moving bodies, and by the black holes
  void calculateForcesFromBodies();
  void calculateForcesFromBlackHoles();

  // Adds the force exerted on each body to each body's net force 
  void updateForce(SimulatedBody &, SimulatedBody &);
  
  // compares the simulated bodies with the black holes, each other and the 
  // boundary. If any overlaps are found, the event is recorded as a collision
  // and the body is removed from the simulation
  void handleOverlaps();

  // if any of the bodies collided with each other
  // the smaller body is removed from the list and the event is recorded
  void handleBodyOverlap();

  // if the two bodies pointed to by the iterator are overlapping, this
  // function will return the body that should be deleted. If neither body
  // should be deleted, this function returns NULL.
  // *TODO* replace with collision decision matrix?
  const ManagedBodyIterator* toBeRemoved(const ManagedBodyIterator*, const ManagedBodyIterator*);

  // records the event and erase the body from the list
  void recordAndErase(std::list<ManagedBody> &, ManagedBodyIterator &, CollisionType);

  // if any of the bodies collided with the boundary
  // the event is recorded and the body is removed from the simulation
  void handleBoundaryOverlap(std::list<ManagedBody> &);

  // if any of the bodies collided with a black hole
  // the event is recorded and the body is removed from the list
  void handleBlackHoleOverlap(std::list<ManagedBody> &, const std::list<SimulatedBody> &);

  // returns: true if the sphere is overlapping the boundary
  bool isOverlappingBoundary(const Sphere &);
  
  // advances the simulation by the time period given
  void advance(double); 

  // Adds the collision event to the list of recorded events
  void recordEvent(const ManagedBody&, double, CollisionType);

  // do not make a copy of this class
  NBodySimulation(const NBodySimulation &);
  NBodySimulation& operator=(const NBodySimulation &);
};

#endif
