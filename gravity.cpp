#include "gravity.h"


NVector<double, 3> Gravity::force(PointMass m1, PointMass m2) 
{
  return force(m1, m2, Gravity::G);
}

NVector<double, 3> Gravity::force(PointMass m1, PointMass m2, const double g_constant) 
{
  NVector<int, 3> intDir = m2.location - m1.location;
  NVector<double, 3> direction; 

  //convert vector<int,3> to vector<double,3>
  direction.setX(intDir.x());
  direction.setY(intDir.y());
  direction.setZ(intDir.z());

  int dotProduct = NVector<int, 3>::dotProduct(m1.location, m2.location);
  return direction * (g_constant * m1.mass * m2.mass / pow(dotProduct, 3));
}

