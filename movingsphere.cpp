#include "movingsphere.h"

//default ctor
MovingSphere::MovingSphere()
  : velocity_(0,0,0)
{}

MovingSphere::MovingSphere(const Vector3 &position, int radius, const Vector3 &velocity) 
{
  center_ = position;
  velocity_ = velocity;
  radius_ = radius;
}

void MovingSphere::transform(const Vector3 &vector) {
  velocity_.transform(vector);
}

//Setters
void MovingSphere::setVelocity(int vx, int vy, int vz) {
  velocity_ = Vector3(vx, vy, vz);
}

void MovingSphere::setVelocity(const Vector3 &vel) {
  velocity_ = vel;
}

//getters
Vector3 MovingSphere::getVelocity() const {
  return velocity_;
}
