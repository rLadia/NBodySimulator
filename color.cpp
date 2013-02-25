#include "color.h"

Color::Color Color::toColor(const std::string &string)
{
  std::string in = string;
  std::transform(in.begin(), in.end(), in.begin(), ::tolower); //conver to lower case

  if(in == "black")
    return Color::kBlack;
  if(in == "white")
    return Color::kWhite;
  if(in == "red")
    return Color::kRed;
  if(in == "green")
    return Color::kGreen;
  if(in == "blue")
    return Color::kBlue;
  if(in == "yellow")
    return Color::kYellow;

  return Color::kBlack;
}

const char* Color::toString(Color color)
{
  return color_names[color];
}