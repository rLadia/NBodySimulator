#include "TableLogger.h"
#include <boost/foreach.hpp>

TableLogger::TableLogger()
  :header_space_(' ', 3)
{}

TableLogger::TableLogger(const std::vector<HeaderStyle> &header)
  :header_(header), header_space_(' ', 3)
{}

void TableLogger::LogTableHead()
{
  using std::cout;
  cout << "Sphere Ellimination Records" << "\n";
  cout << "==========================" << "\n";
  cout << "Index   Color   Time (s)   Event type" << "\n";
  cout << "-----   -----   --------   ----------" << "\n";
}

void TableLogger::LogTableRow(std::vector<std::string> data)
{
  static const unsigned int kIndexHeaderWidth = 5;

  using std::cout;
  BOOST_FOREACH(const std::string& s, data) {
    cout << center(s, kIndexHeaderWidth);
    cout << header_space_;
    cout << "\n";
  }
}

std::string TableLogger::center(const std::string &s, std::string::size_type length) 
{
  if(s.length() > length) 
    return s.substr(0, length);

  std::string result(length, ' ');
  int spaces = (length - s.length()) / 2;

  for(unsigned int i = 0; i < s.length(); ++i)
    result[i+spaces] = s[i];
  return result;
}
