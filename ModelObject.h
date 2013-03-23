#ifndef LADIA_NBODYSIMULATOR_MODELOBJECT_H
#define LADIA_NBODYSIMULATOR_MODELOBJECT_H

#include "nvector.h"

class ModelObject
{
public:
  typedef NVector<double, 3> Vector3D;

  // ctors
  ModelObject();

  // position, velocity, force, mass, radius
  ModelObject(Vector3D, Vector3D, Vector3D, double, double);

  // getters
  const Vector3D getPosition() const;
  const Vector3D getVelocity() const;
  const Vector3D getForce() const;
  const double   getMass() const;
  const double   getRadius() const;

  // setters
  Vector3D setPosition(Vector3D) const;
  Vector3D setVelocity(Vector3D) const;
  Vector3D setForce(Vector3D) const;
  double   setMass(double) const;
  
protected:
  Vector3D position_;
  Vector3D velocity_;
  Vector3D force_;

  double mass_;
  double radius_; // *TODO* generalize to shape
};

#endif
