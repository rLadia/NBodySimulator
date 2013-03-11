#include <string>
#include <vector>
#include <iostream>

class TableLogger 
{
public:
  enum Justification {
    left, right, center
  };

  // column header, justification
  typedef std::pair<std::string, Justification> HeaderStyle;

  // initialize with header
  TableLogger();
  TableLogger(const std::vector<HeaderStyle> &);

  void LogTableHead();
  void LogTableRow(std::vector<std::string> data);

private:
  std::vector<HeaderStyle> header_;
  std::string header_space_;

  // Returns a new string of length n, containing the given string centered
  // surrounded on either side with an equal number of spaces
  // If the given string does not fit in the given length, it is truncated to fit
  std::string center(const std::string &s, std::string::size_type length);

};