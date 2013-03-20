/* converts the model coordinates into console screen coordinates
 * and draws a character on the console
*/
#include "display.h"
#include <iostream>
#include <boost/foreach.hpp>

void Display::Draw(const std::vector<Point> &points)
{
  system("cls"); // *TODO* replace with portable method

  for(int i = 0; i < view_width_; ++i)
    for(int j = 0; j < view_height_; ++j) 
      grid_[i][j] = false;

  BOOST_FOREACH(const Point& p, points) {
    int x = static_cast<int>(p.x() / static_cast<double>(model_width_) * view_width_);
    int y = static_cast<int>(p.y() / static_cast<double>(model_height_) * view_height_);
    if(x >= 0 && x < view_width_ && y >=0 && y < view_height_)
      grid_[x][y] = true;
  }

  std::string top_border(view_width_ + 2, '_');
  std::cout << top_border << "\n";

  for(int i = 0; i < view_height_; ++i) {
    std::cout << "|";
    for(int j = 0; j < view_width_; ++j) {
      if(grid_[j][i])
        std::cout << "O";
      else 
        std::cout << " ";
    }
    std::cout << "|\n";
  }

  std::cout << top_border << std::endl;
}
  
// initialize with height and width
Display::Display(const int height, const int width)
  :model_height_(height), model_width_(width), view_width_(45), view_height_(45)
{  
  boost::array<array_type::index, 2> shape = {{ view_width_, view_height_ }};
  grid_.resize(shape);
}
