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

   const char* color_names[] = { "black", "white", "red", "green", "blue", "yellow" };

   const char* toString(Color color)
   {
     return color_names[color];
   }

   Color toColor(const std::string &string) 
   {
     std::string in = string;
     std::transform(in.begin(), in.end(), in.end(), ::tolower); //conver to lower case

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

};

#endif