#ifndef PANCAKE_ASSETS
#define PANCAKE_ASSETS

#include <map>
#include <string>
#include "../Graphic/Texture.h"
#include "../Graphic/Painter.h"

class Assets {
private:
  std::map<std::string, Texture> textures;

public:
  Assets();
  
  void cleanup();
  
  Texture& loadTexture(const std::string& file);
  
  unsigned long count();
};

#endif //PANCAKE_ASSETMANAGER
