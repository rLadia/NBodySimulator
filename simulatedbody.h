#ifndef LADIA_CSS342_SIMULATEDBODY_H
#define LADIA_CSS342_SIMULATEDBODY_H

#include "movingsphere.h"


//Holds the properties of a simulated sphere
class SimulatedBody
  : public MovingSphere 
{
public:
  //default ctor
  SimulatedBody();

  //location, radius, velocity, force, mass
  SimulatedBody(const Vector3 &, int, const Vector3 &, const Vector3 &, int);

  // advances position based on current velocity, acceleration and force
  // using the kinematic forumlas: 
  //  x(t) = x(0) + v(0) * t + 1/2 * a * t^2
  //  v(t) = v(0) + a * t
  void advance(double);

  //setters
  void setMass(int);
  void setForce(const Vector3 &);

  //getters
  int getMass() const;
  Vector3 getForce() const;

private:
  Vector3 force_;
  int mass_;
};

#endif