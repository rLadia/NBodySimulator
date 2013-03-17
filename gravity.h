#ifndef LADIA_CSS342_GRAVITY_H
#define LADIA_CSS342_GRAVITY_H

#include "nvector.h"

// Namespace containing functions for calculating the gravitational force 
// between objects
namespace Gravity {
  static const double G = 6.67398e-11;

  struct PointMass {
    int mass;
    NVector<double, 3> location;
  };

  // returns the gravitational force between two point masses
  NVector<double, 3> force(PointMass, PointMass);

  // returns the gravitational force between two point masses
  // using a custom value for the gravitational constant
  NVector<double, 3> force(PointMass, PointMass, const double); 
}

#endif
