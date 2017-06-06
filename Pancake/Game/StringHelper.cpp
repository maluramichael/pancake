#include <string>
#include <vector>
#include <cstdlib>
#include "StringHelper.h"

std::vector<std::string> split(const std::string& s, char seperator) {
  std::vector<std::string> output;
  std::string::size_type prev_pos = 0, pos = 0;
  
  while ((pos = s.find(seperator, pos)) != std::string::npos) {
    std::string substring(s.substr(prev_pos, pos - prev_pos));
    
    output.push_back(substring);
    
    prev_pos = ++pos;
  }
  
  output.push_back(s.substr(prev_pos, pos - prev_pos)); // Last word
  
  return output;
}

std::string getValue(const std::string& s) {
  return s.substr(s.find_first_of("\"") + 1, s.length() - s.find_first_of("\"") - 2);
}

int getInt(const std::string& s) {
  return atoi(getValue(s).c_str());
}

std::string trimLeading(const std::string& str) {
  auto pos = str.find_first_not_of(" \t");
  if (pos != std::string::npos) {
    return str.substr(pos);
  }
  return str;
}

std::string trimTailing(const std::string& str) {
  auto pos = str.find_last_not_of(" \t");
  if (pos != std::string::npos) {
    return str.substr(0, pos + 1);
  }
  return str;
}

std::string trim(const std::string& str) {
  return trimLeading(trimTailing(str));
}
