//
// Created by Michael Malura on 17/11/16.
//

#ifndef GAME_STRINGHELPER_H
#define GAME_STRINGHELPER_H

#include <vector>
#include <string>
#include <istream>

namespace Pancake {
  
  std::vector<std::string> split(const std::string& s, char seperator);
  
  std::string getValue(const std::string& s);
  
  int getInt(const std::string& s);
  
  std::string trimLeading(const std::string& str);
  
  std::string trimTrailing(const std::string& str);
  
  std::string trim(const std::string& str);
}

#endif //GAME_STRINGHELPER_H
