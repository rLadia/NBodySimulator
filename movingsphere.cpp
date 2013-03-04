#include "movingsphere.h"

// default ctor
MovingSphere::MovingSphere()
  : velocity_(0,0,0)
{}

// Creates a sphere with the properties of position, radius and velocity
MovingSphere::MovingSphere(const Vector3 &position, int radius, const Vector3 &velocity) 
{
  center_ = position;
  velocity_ = velocity;
  radius_ = radius;
}

// changes the position based on the current velocity and given time interval
void MovingSphere::advance(const double time) {
  center_ += velocity_ * time;
}

// adds the given vector to the internal vector
void MovingSphere::transform(const Vector3 &vector) {
  center_ += vector;
}

//Setters
void MovingSphere::setVelocity(const Vector3 &vel) {
  velocity_ = vel;
}

//getters
Vector3 MovingSphere::getVelocity() const {
  return velocity_;
}
