#include "sphere.h"

//radius defaults to 1
Sphere::Sphere() 
  :center_(0, 0, 0), radius_(1)
{}

//if radius is < 1, it default to 1
Sphere::Sphere(Vector3 center, int radius)
  : center_(center), radius_ ((radius > 0) ? radius : 1)
{}

//calculates and returns surface area
double Sphere::calculateSurfaceArea() const
{
 	return 4 * M_PI * pow(radius_, 2);   
}

//calculates and returns volume
double Sphere::calculateVolume() const 
{
 	return 4.0 / 3.0 * M_PI * pow(radius_, 3);   
}
//setters
void Sphere::setCenter(Vector3 podouble)
{
	center_ = podouble;
}

//if the radius is < 1, it is not changed
void Sphere::setRadius(int radius)
{
	if(radius > 0)
		radius_ = radius;
}

//getters
int Sphere::getRadius() const
{
	return radius_;
}

Vector3 Sphere::getCenter() const
{
  return center_;
}
