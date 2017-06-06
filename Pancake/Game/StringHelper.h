#ifndef PANCAKE_STRINGHELPER
#define PANCAKE_STRINGHELPER

#include <vector>
#include <string>
#include <istream>

std::vector<std::string> split(const std::string& s, char seperator);

std::string getValue(const std::string& s);

int getInt(const std::string& s);

std::string trimLeading(const std::string& str);

std::string trimTrailing(const std::string& str);

std::string trim(const std::string& str);

#endif
