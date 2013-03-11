#include "TableLogger.h"
#include <boost/foreach.hpp>
#include <cassert>

TableLogger::TableLogger(
  const std::string& title, const std::vector<HeaderStyle> &header)
  :title_(title), header_(header), header_space_(3, ' ')
{}

void TableLogger::LogTableHead()
{
  using std::cout;

  cout << title_ << "\n";

  BOOST_FOREACH(const HeaderStyle& h, header_) {
    cout << h.first << header_space_;
  }
  cout << "\n";
}

void TableLogger::LogTableRow(std::vector<std::string> data)
{
  assert(("Row data does not align with available columns.", 
    data.size() == header_.size()));

  using std::cout;
  for(int i = 0; i < data.size(); ++i) {
    cout << center(data[i], header_[i].first.length());
    cout << header_space_;
  }
  cout << "\n";
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
