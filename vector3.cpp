#include "vector3.h"

//default ctor
Vector3::Vector3() 
{}

//3d point ctor
Vector3::Vector3(int x, int y, int z) 
{
  move(x, y, z);
}

//moves the point to the given coordinates
void Vector3::move(int x, int y, int z) 
{
  val_[0] = x;
  val_[1] = y;
  val_[2] = z;
}

//moves the point by the given amount
void Vector3::transform(const Vector3 &vel) 
{
  transform(vel.x(), vel.y(), vel.z());
}

void Vector3::transform(int dx, int dy, int dz)
{
 	val_[0] += dx;
  val_[1] += dy;
  val_[2] += dz;
}

//getters
int Vector3::x() const
{
  return val_[0];
}

int Vector3::y() const
{
  return val_[1];
}

int Vector3::z() const
{
  return val_[2];
}

//overloaded operators
const int Vector3::operator[](const int index) const 
{
  assert(index >= 0 && index < VECTORSIZE);
  return val_[index];
}

Vector3& Vector3::operator+=(const Vector3& rhs) 
{
  for(int i = 0; i < VECTORSIZE; ++i)
    val_[i] += rhs.val_[i];
  return *this;
}

const Vector3 Vector3::operator+(const Vector3& rhs) 
{
  Vector3 result = *this;
  result += rhs;
  return result;
}

Vector3& Vector3::operator-=(const Vector3& rhs) 
{
  for(int i = 0; i < VECTORSIZE; ++i)
    val_[i] -= rhs.val_[i];
  return *this;
}

const Vector3 Vector3::operator-(const Vector3& rhs) 
{
  Vector3 result = *this;
  result -= rhs;
  return result;
}
