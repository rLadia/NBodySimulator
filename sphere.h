#ifndef LADIA_CSS342_SPHERE_H
#define LADIA_CSS342_SPHERE_H

#include "nvector.h"

class Sphere {
  protected:
  Vector3 center_;
  int radius_; 
  
  public:
  Sphere(); //default ctor, radius defaults to 1
  
  //if radius is < 0, radius defaults to 1
  Sphere(Vector3, int); //center, radius
  
  double calculateSurfaceArea() const;
  double calculateVolume() const;

	//setters
	void setCenter(Vector3);
	void setRadius(int); //radius must be > 0, otherwise, no change is made
  
	//getters
	Vector3 getCenter() const;
	int getRadius() const;
};

#endif
