#ifndef LADIA_NBODY_DISPLAY
#define LADIA_NBODY_DISPLAY

#include <vector>
#include <boost/multi_array.hpp>
#include "../src/nvector.h"

class Display
{
public:
  typedef NVector<int, 2> Point;

  void Draw(const std::vector<Point> &);

  // initialize with height and width
  Display(const int, const int);

private:
  // dimensions of data to be displayed
  int model_height_;
  int model_width_;

  int view_height_;
  int view_width_;

  typedef boost::multi_array<bool, 2> array_type;

  array_type grid_;
};

#endif
