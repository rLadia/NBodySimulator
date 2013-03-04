#include "color.h"

// matches the given string to the enum values and returns the appropriate value
// if no match was found, it returns kBlack
Color::Color Color::toColor(const std::string &string)
{
  std::string in = string;
  std::transform(in.begin(), in.end(), in.begin(), ::tolower); //convert to lower case

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

// return the string representation of the given color
const char* Color::toString(Color color)
{
  return color_names[color];
}
