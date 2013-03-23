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

  // Modifies the position and velocity using the kinematic equations of motion
  // where acceleration is equal to force divided by mass
  // x(t) = x(0) + v(0) * t + 1/2 a * t^2
  // v(t) = v(0) + a * t
  void Advance(double);

  // getters
  const Vector3D Position() const;
  const Vector3D Velocity() const;
  const Vector3D Force() const;
  const double   Mass() const;
  const double   Radius() const;

  // setters
  void SetPosition(Vector3D);
  void SetVelocity(Vector3D);
  void SetForce(Vector3D);
  void SetMass(double);
  
protected:
  Vector3D position_;
  Vector3D velocity_;
  Vector3D force_;

  double mass_;
  double radius_; // *TODO* generalize to shape
};

#endif
