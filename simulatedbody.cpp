#include "simulatedbody.h"

SimulatedBody::SimulatedBody()
{}

//mass = radius
SimulatedBody::SimulatedBody(const Vector3 &position, int radius, const Vector3 &velocity, const Vector3 &force, int mass)
{
  center_ = position;
  radius_ = radius;
  velocity_ = velocity;
  force_ = force;
  mass_ = mass;
}

//Modifies position and velocity based on current velocity and acceleration
//*TODO* assert( ||v|| < c )
void SimulatedBody::advance(const double time) {
  Vector3 acceleration = force_ * (1.0f / mass_);

  center_ += velocity_ * time;
  center_ += acceleration * 0.5 * time * time; // 1/2 * a * t^2

  velocity_ += acceleration * time; // v(t) = v(0) + at
}

//Setters
void SimulatedBody::setMass(int mass) 
{
  mass_ = mass;
}

void SimulatedBody::setForce(const Vector3& force) 
{
  force_ = force;
}

//Getters
int SimulatedBody::getMass() const 
{
  return mass_;
}

Vector3 SimulatedBody::getForce() const 
{
  return force_;
}