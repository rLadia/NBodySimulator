#ifndef LADIA_CSS342_COLOR_H
#define LADIA_CSS342_COLOR_H

#include <algorithm>
#include <string>

namespace Color {
   enum Color {
      kBlack,
      kWhite,
      kRed, 
      kGreen,
      kBlue,
      kYellow,
   };

   static const char* color_names[] = { "black", "white", "red", "green", "blue", "yellow" };

   const char* toString(Color);

   Color toColor(const std::string &);
};

#endif