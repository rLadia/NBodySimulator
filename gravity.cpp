#include "gravity.h"


NVector<double, 3> Gravity::force(PointMass m1, PointMass m2) 
{
  return force(m1, m2, Gravity::G);
}

NVector<double, 3> Gravity::force(PointMass m1, PointMass m2, const double g_constant) 
{
  NVector<double, 3> direction = m2.location - m1.location;

  double dotProduct = NVector<double, 3>::dotProduct(m1.location, m2.location);
  return direction * (g_constant * m1.mass * m2.mass / pow(dotProduct, 3));
}

