#include "overlap.h"
#include <cmath>

//if the sum of the radius is <= the distance, the spheres collide
bool Overlap::isOverlapping(Shape::Circle left, Shape::Circle right){
  return distance(left.center, right.center) 
    <= left.radius + right.radius;
}

//Returns whether the point exists within the sphere
bool Overlap::isOverlapping(Shape::Circle circle, Shape::Point point){
  return distance(circle.center, point.center) <= circle.radius;
}

//sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
double Overlap::distance(Vector2D a, Vector2D b) 
{
  return sqrt(pow(b.x() - a.x(), 2) + 
      pow(b.y() - a.y(), 2) + pow(b.z() - a.z(), 2));
}