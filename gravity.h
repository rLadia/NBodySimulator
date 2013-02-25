#ifndef LADIA_CSS342_GRAVITY_H
#define LADIA_CSS342_GRAVITY_H

#include <cmath>
#include "nvector.h"

namespace Gravity {
  static const double G = 6.67398e-11;

  struct PointMass {
    int mass;
    NVector<double, 3> location;
  };

  NVector<double, 3> force(PointMass, PointMass);
  NVector<double, 3> force(PointMass, PointMass, const double);
}

#endif