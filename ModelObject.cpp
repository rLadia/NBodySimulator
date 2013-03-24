#include "ModelObject.h"
#include <cmath>

// default ctor
ModelObject::ModelObject()
  : position_(0, 0, 0), velocity_(0, 0, 0), force_(0, 0, 0), mass_(0), shape_(0)
{}

// position, velocity, force, mass, radius
ModelObject::ModelObject(
  Vector3D position, 
  Vector3D velocity, 
  Vector3D force, 
  double mass, 
  double shape)
  : position_(position), 
    velocity_(velocity), 
    force_(force), 
    mass_(mass), 
    shape_(shape)
{}

void ModelObject::Advance(double time)
{
  Vector3 acceleration = force_ * (1.0f / mass_);

  position_ += velocity_ * time; // v(0) * t
  position_ += acceleration * 0.5 * std::pow(time, 2.0); // 1/2 * a * t^2

  velocity_ += acceleration * time; // v(t) = v(0) + at
}

// getters
const ModelObject::Vector3D ModelObject::Position() const
{
  return position_;
}

const ModelObject::Vector3D ModelObject::Velocity() const
{
  return velocity_;
}
const ModelObject::Vector3D ModelObject::Force() const
{
  return force_;
}

const double   ModelObject::Mass() const
{
  return mass_;
}

const double   ModelObject::Shape() const 
{
  return shape_;
}

// setters
void ModelObject::SetPosition(Vector3D position) 
{
  position_ = position;
}

void ModelObject::SetVelocity(Vector3D velocity)
{
  velocity_ = velocity;
}

void ModelObject::SetForce(Vector3D force)
{
  force_ = force;
}

void ModelObject::SetMass(double mass)
{
  mass_ = mass;
}
