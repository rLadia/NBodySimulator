#include "display.h"
#include <iostream>

void Display::Draw(const std::vector<Point> &points)
{
  std::cout << "Draw Called\n"; 
}
  
// initialize with height and width
Display::Display(const int height, const int width)
  :height_(height), width_(width)
{  }
