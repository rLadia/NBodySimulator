#include "collision.h"

//if the sum of the radius is <= the distance, the spheres collide
bool COLLISION::isOverlapping(const Sphere& left, const Sphere& right){
  return distance(left.getCenter(), right.getCenter()) 
    <= left.getRadius() + right.getRadius();
}

//sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
double COLLISION::distance(const Vector3 &a, const Vector3 &b) 
{
  return sqrt(pow(b.x() - a.x(), 2) + 
      pow(b.y() - a.y(), 2) + pow(b.z() - a.z(), 2));
}

//*TODO* research benefits of replacing vector with static arrays
std::vector<double> COLLISION::calculateCollisionTimes(const MovingSphere& left, const MovingSphere& right)
{
  Vector3 pos = right.getCenter() - left.getCenter();
  Vector3 vel = right.getVelocity() - left.getVelocity();
  int radius = right.getRadius() + left.getRadius();

  using std::vector;
  vector<int> x_squared = POLYNOMIAL::square(vel.x(), pos.x());
  vector<int> y_squared = POLYNOMIAL::square(vel.y(), pos.y());
  vector<int> z_squared = POLYNOMIAL::square(vel.z(), pos.z());

  vector<int> squared(3);
   
  for(int i = 0; i < 3; ++i) {
    squared[i] = x_squared[i] + y_squared[i] + z_squared[i];
  }  
  squared[2] -= radius * radius; //subtract r^2 from both sides

  return POLYNOMIAL::quadratic(squared);
}
