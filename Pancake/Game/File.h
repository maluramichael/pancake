#ifndef PANCAKE_FILE
#define PANCAKE_FILE

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

class File {
public:
  std::string path = "";
  
  std::string content = "";
  
  File() = default;
  
  explicit File(const char* path) : path(path) {
  }
  
  void setPath(const std::string& path) {
    File::path = path;
  }
  
  std::string readAll() {
    if (path.empty()) return "";

    std::ifstream stream(path);
    content = "";
    if (stream.is_open()) {
      content = std::string((std::istreambuf_iterator<char>(stream)), (std::istreambuf_iterator<char>()));
      stream.close();
      std::cout << path << " -> " << content << std::endl;
    }
    return content;
  }
};

#endif
