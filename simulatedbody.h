#ifndef LADIA_CSS342_SIMULATEDBODY_H
#define LADIA_CSS342_SIMULATEDBODY_H

#include "movingsphere.h"


// Simulates a body with a position, radius, mass and force
// the body will move through space according to the laws of newtonian motion
class SimulatedBody
  : public MovingSphere // implemented using a sphere approximation
{
public:
  // advances position based on current velocity
  // updates velocity based on current acceleration
  // using the kinematic forumlas: 
  //  v(t) = v(0) + a * t
  void advance(double);

  // setters
  void setMass(int);
  void setForce(const Vector3 &);

  // getters
  int getMass() const;
  Vector3 getForce() const;

  // default ctor
  SimulatedBody();

  // location, radius, velocity, force, mass
  SimulatedBody(const Vector3 &, int, const Vector3 &, const Vector3 &, int);

private:
  Vector3 force_;
  int mass_;
};

#endif
