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

  //setters
  void setMass(int mass);

  //getters
  Color getColor() const;
  int getMass() const;

private:
  Color color_;
  int mass_;
};

#endif