#ifndef LADIA_CSS342_COLOR_H
#define LADIA_CSS342_COLOR_H

#include <algorithm>
#include <string>

// Namespace that contains a color enum and related functions
namespace Color {
   enum Color {
      kBlack,
      kWhite,
      kRed, 
      kGreen,
      kBlue,
      kYellow
   };

   // string array corresponding to enum positions of Color
   // color_names[kBlack] == "black" etc.
   static const char* color_names[] = { "black", "white", "red", "green", "blue", "yellow" };

   // return the string representation of the given color
   const char* toString(Color);

   // matches the given string to the enum values and returns the appropriate value
   // if no match was found, it returns kBlack
   Color toColor(const std::string &);
}

#endif
