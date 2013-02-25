#ifndef LADIA_CSS342_VECTOR_H
#define LADIA_CSS342_VECTOR_H

#include <cassert>
#include <cstddef>

/* 
 * Represents an n-dimensional vector
 */
template<typename T, std::size_t D> //type, dimensions
class Vector
{
  typedef std::size_t size_t;
	T val_[D];
  
  public: 
  Vector(); //default ctor
  Vector(const T, const T); //x, y
  Vector(const T, const T, const T); //x, y, z

  T x() const;
  T y() const;
  T z() const;

  //adds the value of input to current vector 
  void transform(const Vector<T, D> &);
  static double magnitude(const Vector<T, D> &);

  T& operator[](size_t);
  const T operator[](const size_t) const; 

  Vector<T, D>& operator+=(const Vector<T, D> &);
  const Vector<T, D> operator+(const Vector<T, D> &);

  Vector<T, D> & operator-=(const Vector<T, D> &);
  const Vector<T, D> operator-(const Vector<T, D> &);
};

template<typename T, size_t D>
T& Vector<T, D>::operator[](size_t index)
{
  return val_[index];
}

template<typename T, size_t D>
Vector<T, D>::Vector() 
{
  assert(("Vector size must be > 0", D > 0));
}

template<typename T, size_t D>
Vector<T, D>::Vector(const T x, const T y) 
{
  val_[0] = x;
  val_[1] = y;
}

template<typename T, size_t D>
Vector<T, D>::Vector(const T x, const T y, const T z) 
{
  val_[0] = x;
  val_[1] = y;
  val_[2] = z;
}

template<typename T, size_t D>
void Vector<T, D>::transform(const Vector<T, D>& vector) {
  for(int i = 0; i < D; ++i)
    val_[i] += vector[i];
}

template<typename T, size_t D>
T Vector<T, D>::x() const {
  return val_[0];
}

template<typename T, size_t D>
T Vector<T, D>::y() const {
  assert(("y not defined with vector size less than 2", D >= 1));
  return val_[1];
}

template<typename T, size_t D>
T Vector<T, D>::z() const {
  assert(("z not defined with vector size less than 3", D >= 2));
  return val_[2];
}

template<typename T, size_t D>
const T Vector<T, D>::operator[](const size_t index) const {
  assert(("Index out of bounds", index > 0 && index < D));
  return val_[index];
}

template<typename T, size_t D>
Vector<T, D>& Vector<T, D>::operator+=(const Vector<T, D> &rhs) 
{
  for(int i = 0; i < D; ++i)
    val_[i] += rhs.val_[i];
  return *this;
}

template<typename T, size_t D>
const Vector<T, D> Vector<T, D>::operator+(const Vector<T, D> &rhs)
{
  Vector<T, D> result = *this;
  result += rhs;
  return result;
}

template<typename T, size_t D>
Vector<T, D>& Vector<T, D>::operator-=(const Vector<T, D> &rhs)
{
  for(int i = 0; i < D; ++i)
    val_[i] -= rhs.val_[i];
  return *this;
}

template<typename T, size_t D>
const Vector<T, D> Vector<T, D>::operator-(const Vector<T, D> &rhs) 
{
  Vector<T, D> result = *this;
  result -= rhs;
  return result;
}



#endif
