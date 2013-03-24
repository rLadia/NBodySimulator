#ifndef LADIA_CSS342_COLLISION_H
#define LADIA_CSS342_COLLISION_H

#include "Shape.h"

// Namespace holding common functions useful for collsion detection
namespace Overlap 
{
  //return: true if the spheres are overlapping
  bool isOverlapping(Shape::Sphere, Shape::Sphere);

  //return: true if the spheres are overlapping
  bool isOverlapping(Shape::Circle, Shape::Circle);

  // return: true if the point is contained within the sphere
  bool isOverlapping(Shape::Circle, Shape::Point);
}

#endif
