#ifndef LADIA_CSS342_POLYNOMIAL_H
#define LADIA_CSS342_POLYNOMIAL_H

#include <vector>
#include <cmath>
#include <cassert>

// Namespace containing functions used in polynomial equations
namespace POLYNOMIAL {
  using std::vector;

  //Uses the quadratic equation to solve a second degree polynomial
  //pre: the vector's size is 3 and holds the coefficients for a 2nd degree
  //  polynomial of the form ax^2 + bx + c
  //return: the solutions of the polynomial equation, the size of the array 
  //  will be equal to the number of real solutions
  //*TODO* generalize to n-vector?
  template<typename T>
  vector<double> SecondDegreeSolutions(vector<T>); //a, b, c

  //return: vector containing the coefficients of the 2nd degree polynomial 
  //  that results from squaring (ax+b). The resulting polynomial is in the 
  //  form ax^2 + bx + c where a, b and c are represented in the 
  //  returned vector at positions 0, 1 and 2 respectively
  //*TODO* generalize to n-dimensions, look up benefits of using static arrays
  template<typename T>
  vector<T> square(T, T);
}

// returns the solutions of a second degree polynomial
// The size of returned array will equal the number of real solutions
template<typename T>
std::vector<double> POLYNOMIAL::SecondDegreeSolutions(std::vector<T> values) {
  assert(values.size() == 3);
  T a = values[0];
  T b = values[1];
  T c = values[2];

  double r1, r2;
  vector<double> results;

  //if a, b or c are floating point numbers, the precision for radicand needs
  //to be twice the precision of result
  long double radicand = b * b - 4 * a * c; // b^2 - 4ac
  
  //no real results or a non-quadratic function, return empty array
  if(radicand < 0 || a == 0) {
    // do nothing

  } else if(radicand == 0) { // one real root
    r1 = - 1.0f * b / (2 * a);
    results.push_back(r1);

  } else { // two real roots

    double det = sqrt(radicand); 
      
    if(b < 0) {
      r1 = (-1 * b + det) / (2.0f * a);
    } else { // prevents errors from catastrophic cancellation
      r1 = (-1 * b - det) / (2.0f * a);
    }

    // Viete's Formula, from wikipedia article on loss of significance
    r2 = c / (a * r1); 

    results.push_back(r1);
    results.push_back(r2);
  }

  return results;
}

//*TODO* limit checks
//*TODO* generalize for n-vector multiplication
template<typename T>
std::vector<T> POLYNOMIAL::square(T a, T b) 
{
  std::vector<T> result(3);
  result[0] = a * a; 
  result[1] = 2 * a * b;
  result[2] = b * b;
  return result;
}

#endif
