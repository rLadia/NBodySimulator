#ifndef LADIA_CSS342_POLYNOMIAL_H
#define LADIA_CSS342_POLYNOMIAL_H

#include <vector>
#include <cmath>
#include <cassert>

//contains commonly used functions used for polynomial equations
namespace POLYNOMIAL {
  using std::vector;

  //Uses the quadratic equation to solve a second degree polynomial
  //pre: the vector's size is 3 and holds the coefficients for a 2nd degree
  //  polynomial of the form ax^2 + bx + c
  //return: the solutions of the polynomial equation, the size of the array 
  //  will be equal to the number of real solutions
  //*TODO* rename to solutions? generalize to n-vector?
  vector<double> quadratic(vector<int>); //a, b, c

  //return: vector containing the coefficients of the 2nd degree polynomial 
  //  that results from squaring (ax+b). The resulting polynomial is in the 
  //  form ax^2 + bx + c where a, b and c are represented in the 
  //  returned vector at positions 0, 1 and 2 respectively
  //*TODO* generalize to n-dimensions, look up benefits of using static arrays
  vector<int> square(int, int); 
}

#endif
