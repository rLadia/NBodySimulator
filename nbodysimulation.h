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

static const double kTimeInterval = .01;
static const int kGravity = 10;

// Simulates the motion of 3d bodies through space
class NBodySimulation {
public:
  enum CollisionType {
    kCollision, // collided with another body
    kBlackHole, // collided with the black hole
    kBoundary   // collided with the boundary
  };

  // Contains user accessible information about a collision
  struct Record {
    int index; // the index of the sphere that collided
    Color::Color color;
    double time; // the time of collision
    CollisionType collision; // the type of collision that occurred
  };

  // Adds a body to be simulated.
  // Each body consists of a color, position, radius and initial velocity. 
  // Each body will be assigned an index based on the order that it was added
  // to the simulation.
  void addBody(Color::Color, const Vector3 &, int, const Vector3 &);
  
  // Adds a black hole to be simulated
  // A black hole consists of a position and a mass. Black holes are not 
  // affected by other bodies and simply act as a point source of gravity.
  void addBlackHole(const Vector3 &, int);

  // Returns a vector containing records on all of the events that have 
  // occurred. Each record consists of the index and color of body that was 
  // removed, the time of collision, and the type of collision. 
  std::vector<Record> getSimulationResults();

  // Runs the simulation until no bodies remain
  // Bodies will be removed from the simulation when they collide 
  // with a black hole, the boundary, a black sphere, or a larger (by radius) 
  // sphere. Every time a body is removed, a record will be added that can be
  // accessed by calling getSimulationResults().
  // *TODO* add check for stable orbits
  void runSimulation(); 

  // removes all simulated bodies and black holes and resets the 
  // simulation to its initial state
  void reset();

  NBodySimulation(unsigned int); //boundary size

private:

  //associates a body with an index value and color
  struct ManagedBody {
    int index;
    SimulatedBody body;
    Color::Color color;
    bool isDead;
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
  
  // Sets the net force of each simulated body to 0
  void resetForces();

  // Updates the net instantaneous force exerted on each simulated body
  // There are gravitational forces acting between each body and from
  // black holes. The black spheres are not affected by gravity.
  void updateAllForces();

  // Calculates the instantaneous forces exerted on the simulated bodies
  // from each other body and from the black hole
  void calculateForcesFromBodies();
  void calculateForcesFromBlackHoles();

  // Adds the gravitational force between each body to each body's net force
  void addForcesBetween(SimulatedBody &, SimulatedBody &);
  
  // Compares the simulated bodies with the black holes, each other and the 
  // boundary. If any overlaps are found, the event is recorded as a collision
  // and the body is marked as ready to be removed from the simulation
  void recordAndMarkCollisions();

  // Compares each body to each other body and looks for overlaps.
  // If any overlaps are found, the smaller body is marked for removal and the
  // event is recorded as a collision. Black spheres are bigger than all other 
  // spheres for purposes of comparisons.
  void handleBodyOverlap();

  // Compares each body to each black hole and looks for overlaps. If any 
  // overlaps are found, the body is marked for removal and the event 
  // is recorded as a black hole collision.
  void handleBlackHoleOverlap(
    std::list<ManagedBody> &, const std::list<SimulatedBody> &);

  // Compares each body to the boundary and looks for overlaps. If any 
  // overlaps are found, the body is marked for removal and the event 
  // is recorded as a boundary collision.
  void handleBoundaryOverlap(std::list<ManagedBody> &);

  // Returns true if the sphere is in contact over overlapping the boundary
  bool isOverlappingBoundary(const Sphere &);

  // Removes bodies from the simulation that have lost collisions
  void removeDeadBodies();

  // Returns the body that should be deleted in a collision.
  // If neither body should be deleted, this function returns NULL.
  // *TODO* replace with decision matrix?
  const ManagedBodyIterator* toBeRemoved(
    const ManagedBodyIterator*, const ManagedBodyIterator*);

  // Records the event and marks the body as ready to be removed from the list
  void recordAndMarkForDeletion(ManagedBody &, CollisionType);
  
  // Advances the simulation by the time period given
  // Each body will move according to its current velocity and the net force
  void advance(double); 

  // Adds the collision event to the list of recorded events
  void recordEvent(const ManagedBody&, double, CollisionType);

  // do not make a copy of this class
  NBodySimulation(const NBodySimulation &);
  NBodySimulation& operator=(const NBodySimulation &);
};

#endif
