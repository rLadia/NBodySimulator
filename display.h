#ifndef LADIA_NBODY_DISPLAY
#define LADIA_NBODY_DISPLAY

#include <vector>
#include "nvector.h"

class Display 
{
public:
  typedef NVector<double, 2> Point;

  void Draw(const std::vector<Point> &);
  
  // initialize with height and width
  Display(const int, const int);

private:
  // dimensions of data to be displayed
  int height_;
  int width_;
};

#endif
