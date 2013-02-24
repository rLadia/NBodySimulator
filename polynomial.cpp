#include "polynomial.h"

//returns the solutions of a second degree polynomial
//The size of returned array will equal the number of real solutions
std::vector<double> POLYNOMIAL::quadratic(std::vector<int> values) {
  assert(values.size() == 3);
  int a = values[0];
  int b = values[1];
  int c = values[2];

  double r1, r2;
  vector<double> results;

  //possible overflow? 
  //if a, b or c are floating point numbers, the precision for radicand needs
  //to be twice the precision of result
  int radicand = b * b - 4 * a * c; // b^2 - 4ac
  
  //no real results or a non-quadratic function, return empty array
  if(radicand < 0 || a == 0) {
    //do nothing
  } else if(radicand == 0) {//one real root
    r1 = - 1.0f * b / (2 * a);
    results.push_back(r1);
  } else {

    double det = sqrt(radicand); 
      
    if(b < 0) {
      r1 = (-1 * b + det) / (2.0f * a);
    } else { //prevents errors from catastrophic cancellation
      r1 = (-1 * b - det) / (2.0f * a);
    }

    //Viete's Formula, from wikipedia article on loss of significance
    r2 = c / (a * r1); 

    results.push_back(r1);
    results.push_back(r2);
  }

  return results;
}

//*TODO* limit checks
//*TODO* generalize for n-vector multiplication
std::vector<int> POLYNOMIAL::square(int a, int b) 
{
  std::vector<int> result(3);
  result[0] = a * a; 
  result[1] = 2 * a * b;
  result[2] = b * b;
  return result;
}


