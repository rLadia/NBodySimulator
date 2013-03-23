#include "ModelObject.h"

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

const double   ModelObject::Radius() const 
{
  return radius_;
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
