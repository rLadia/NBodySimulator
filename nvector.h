#ifndef LADIA_CSS342_NVECTOR_H
#define LADIA_CSS342_NVECTOR_H

#include <cassert>
#include <cstddef>

/* 
 * Represents an n-dimensional Vector
 */
template<typename T, std::size_t D> //type, dimensions
class NVector
{
  typedef std::size_t size_t;
	T val_[D];
  
  public: 
  NVector(); //default ctor
  NVector(const T, const T); //x, y
  NVector(const T, const T, const T); //x, y, z

  T x() const;
  T y() const;
  T z() const;

  void setX(const T);
  void setY(const T);
  void setZ(const T);

  //adds the value of input to current NVector 
  void transform(const NVector<T, D> &);
  static T dotProduct(const NVector<T, D> &, const NVector<T, D> &);

  T& operator[](size_t);
  const T operator[](const size_t) const; 

  //overloaded mathematical operators
  NVector<T, D>& operator*=(const double);
  NVector<T, D>& operator*=(const int);

  const NVector<T, D> operator*(const double) const;
  const NVector<T, D> operator*(const int) const;
  
  NVector<T, D>& operator+=(const NVector<T, D> &);
  const NVector<T, D> operator+(const NVector<T, D> &) const;

  NVector<T, D> & operator-=(const NVector<T, D> &);
  const NVector<T, D> operator-(const NVector<T, D> &) const;
};

template<typename T, size_t D>
T& NVector<T, D>::operator[](size_t index)
{
  return val_[index];
}

template<typename T, size_t D>
NVector<T, D>::NVector() 
{
  assert(("NVector size must be > 0", D > 0));
}

template<typename T, size_t D>
NVector<T, D>::NVector(const T x, const T y) 
{
  val_[0] = x;
  val_[1] = y;
}

template<typename T, size_t D>
NVector<T, D>::NVector(const T x, const T y, const T z) 
{
  val_[0] = x;
  val_[1] = y;
  val_[2] = z;
}

template<typename T, size_t D>
void NVector<T, D>::transform(const NVector<T, D>& NVector) {
  for(int i = 0; i < D; ++i)
    val_[i] += NVector[i];
}

template<typename T, size_t D>
T NVector<T, D>::dotProduct(const NVector<T, D>& NVector1, const NVector<T, D>& NVector2) {
  T sum = 0;
  for(int i = 0; i < D; ++i)
    sum += NVector1.val_[i] * NVector2.val_[i];
  return sum;
}

//setters
template<typename T, size_t D>
void NVector<T, D>::setX(const T x) {
  val_[0] = x;
}

template<typename T, size_t D>
void NVector<T, D>::setY(const T y) {
  assert(("y not defined with NVector size less than 2", D >= 1));
  val_[1] = y;
}

template<typename T, size_t D>
void NVector<T, D>::setZ(const T z) {
  assert(("z not defined with NVector size less than 3", D >= 2));
  val_[2] = z;
}

template<typename T, size_t D>
T NVector<T, D>::x() const {
  return val_[0];
}

//getters

template<typename T, size_t D>
T NVector<T, D>::y() const {
  assert(("y not defined with NVector size less than 2", D >= 1));
  return val_[1];
}


template<typename T, size_t D>
T NVector<T, D>::z() const {
  assert(("z not defined with NVector size less than 3", D >= 2));
  return val_[2];
}

template<typename T, size_t D>
const T NVector<T, D>::operator[](const size_t index) const {
  assert(("Index out of bounds", index > 0 && index < D));
  return val_[index];
}


//overloaded operators
template<typename T, size_t D>
NVector<T, D>& NVector<T, D>::operator*=(const double scalar) 
{
  for(int i = 0; i < D; ++i)
    val_[i] *= scalar;
  return *this;
}

template<typename T, size_t D>
const NVector<T, D> NVector<T, D>::operator*(const double scalar) const
{
  NVector<T, D> result = *this;
  result *= scalar;
  return result;
}

template<typename T, size_t D>
NVector<T, D>& NVector<T, D>::operator*=(const int scalar) 
{
  for(int i = 0; i < D; ++i)
    val_[i] *= scalar;
  return *this;
}

template<typename T, size_t D>
const NVector<T, D> NVector<T, D>::operator*(const int scalar) const
{
  NVector<T, D> result = *this;
  result *= scalar;
  return result;
}

template<typename T, size_t D>
NVector<T, D>& NVector<T, D>::operator+=(const NVector<T, D> &rhs) 
{
  for(int i = 0; i < D; ++i)
    val_[i] += rhs.val_[i];
  return *this;
}

template<typename T, size_t D>
const NVector<T, D> NVector<T, D>::operator+(const NVector<T, D> &rhs) const
{
  NVector<T, D> result = *this;
  result += rhs;
  return result;
}

template<typename T, size_t D>
NVector<T, D>& NVector<T, D>::operator-=(const NVector<T, D> &rhs)
{
  for(int i = 0; i < D; ++i)
    val_[i] -= rhs.val_[i];
  return *this;
}

template<typename T, size_t D>
const NVector<T, D> NVector<T, D>::operator-(const NVector<T, D> &rhs) const
{
  NVector<T, D> result = *this;
  result -= rhs;
  return result;
}

#endif
