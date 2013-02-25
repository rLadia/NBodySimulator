#include "simulatedbody.h"

SimulatedBody::SimulatedBody()
{}

//mass = radius
SimulatedBody::SimulatedBody(Color color, const Vector3 &position, int radius, const Vector3 &velocity) 
{
  color_ = color;
  center_ = position;
  velocity_ = velocity;
  radius_ = radius;
  mass_ = radius;
}

void SimulatedBody::setMass(int mass) 
{
  mass_ = mass;
}

Color::Color SimulatedBody::getColor() const 
{
  return color_;
}

int SimulatedBody::getMass() const 
{
  return mass_;
}