#ifndef LADIA_CSS342_MOVINGSPHERE_H
#define LADIA_CSS342_MOVINGSPHERE_H

#include "sphere.h"

// Adds velocity property to Sphere
class MovingSphere : public Sphere {

  protected:
  Vector3 velocity_;

  public:
  MovingSphere();

  // Creates a sphere with the properties of position, radius and velocity
  MovingSphere(const Vector3 &, int, const Vector3 &);

  // changes the position of the sphere by the given vector
  void transform(const Vector3 &);

  // changes the position based on the current velocity and given time interval
  void advance(const double); 

  // setters
  void setVelocity(const Vector3 &);

  // getters
  Vector3 getVelocity() const;
};

#endif
