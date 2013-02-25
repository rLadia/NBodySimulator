#ifndef LADIA_CSS342_MOVINGSPHERE_H
#define LADIA_CSS342_MOVINGSPHERE_H

#include "sphere.h"

//Adds velocity property to Sphere
class MovingSphere : public Sphere {

  protected:
  Vector3 velocity_;

  public:
  MovingSphere();
  MovingSphere(const Vector3 &, int, const Vector3 &);

  // adds the given vector to the internal vector
  void transform(const Vector3 &);

  //setters
  void setVelocity(int, int, int);
  void setVelocity(const Vector3 &);

  //getters
  Vector3 getVelocity() const;
};

#endif
