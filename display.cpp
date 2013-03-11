#include "display.h"
#include <iostream>
#include <boost/foreach.hpp>

void Display::Draw(const std::vector<Point> &points)
{
  system("cls");
  for(int i = 0; i < view_width_; ++i)
    for(int j = 0; j < view_height_; ++j) 
      grid_[i][j] = false;

  BOOST_FOREACH(const Point& p, points) {
    int x = static_cast<int>(p.x() / static_cast<double>(model_width_) * view_width_);
    int y = static_cast<int>(p.y() / static_cast<double>(model_height_) * view_height_);
    grid_[x][y] = true;
  }

  for(int i = 0; i < view_height_; ++i) {
    std::cout << i;
    for(int j = 0; j < view_width_; ++j) {
      if(grid_[j][i])
        std::cout << "X";
      else 
        std::cout << " ";
    }
    std::cout << "\n";
  }
}
  
// initialize with height and width
Display::Display(const int height, const int width)
  :model_height_(height), model_width_(width), view_width_(75), view_height_(75)
{  
  boost::array<array_type::index, 2> shape = {{ view_width_, view_height_ }};
  grid_.resize(shape);
}
