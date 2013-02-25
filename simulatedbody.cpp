#include "simulatedbody.h"

SimulatedBody::SimulatedBody()
{}

//mass = radius
SimulatedBody::SimulatedBody(const Vector3 &position, int radius, const Vector3 &velocity) 
{
  center_ = position;
  velocity_ = velocity;
  radius_ = radius;
  mass_ = radius;
}

//Modifies position and velocity based on current velocity and acceleration
//*TODO* assert( ||v|| < c )
void SimulatedBody::advance(const double time) {
  center_ += velocity_ * time;
  center_ += acceleration_ * 0.5 * time * time; // 1/2 * a * t^2

  velocity_ += acceleration_ * time; // v(t) = v(0) + at
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