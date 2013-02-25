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

//Setters
void SimulatedBody::setMass(int mass) 
{
  mass_ = mass;
}

void SimulatedBody::setAcceleration(const Vector3& acceleration) 
{
  acceleration_ = acceleration;
}

void SimulatedBody::setForce(const Vector3& force) 
{
  acceleration_ = force;
}

//Getters
Color::Color SimulatedBody::getColor() const 
{
  return color_;
}

int SimulatedBody::getMass() const 
{
  return mass_;
}

Vector3 SimulatedBody::getAcceleration() const 
{
  return acceleration_;
}

Vector3 SimulatedBody::getForce() const 
{
  return force_;
}