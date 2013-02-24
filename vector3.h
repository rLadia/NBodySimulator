#ifndef LADIA_CSS342_Vector3_H
#define LADIA_CSS342_Vector3_H

#include <cassert>

/* 
 * Represents a 3D vector
 */
class Vector3
{
  static const int VECTORSIZE = 3;
	int val_[3];
  
  public:
  Vector3(); //default ctor
  
  //x, y, z
  Vector3(int, int, int); 
  
  
  //getters
  int x() const;
  int y() const;
  int z() const;

  //sets the point to coordinate x, y, z
  void move(int, int, int); 
  
  //moves the point by dX, dY, dZ
  void transform(int, int, int);
  void transform(const Vector3 &);

  const int operator[](const int) const;

  Vector3& operator+=(const Vector3&);
  const Vector3 operator+(const Vector3&);

  Vector3& operator-=(const Vector3&);
  const Vector3 operator-(const Vector3&);
};

#endif
