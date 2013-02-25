#ifndef LADIA_CSS342_SIMULATEDBODY_H
#define LADIA_CSS342_SIMULATEDBODY_H

#include "color.h"
#include "movingsphere.h"


//Holds the properties of a simulated sphere
class SimulatedBody
  : public MovingSphere 
{
  typedef Color::Color Color;

public:
  //default ctor
  SimulatedBody();

  //sets the mass equal to the radius
  SimulatedBody(Color, const Vector3 &, int, const Vector3 &);

  // advances position based on current velocity, acceleration and force
  void advance(double);

  //setters
  void setMass(int);
  void setAcceleration(const Vector3 &);
  void setForce(const Vector3 &);

  //getters
  Color getColor() const;
  int getMass() const;
  Vector3 getAcceleration() const;
  Vector3 getForce() const;

private:
  Vector3 force_;
  Vector3 acceleration_;
  Color color_;
  int mass_;
};

#endif