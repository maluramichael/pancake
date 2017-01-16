//
// Created by Michael Malura on 22/11/16.
//


#include <string>
#include <fstream>
#include <vector>

#include "../include/StringHelper.h"
#include "../include/MapLoader.h"

namespace Pancake {

    MapLoader::MapLoader(std::string path) {
        std::ifstream file;
        file.open(path);
        std::string line;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (line.find("SubTexture") != std::string::npos) {
                    std::vector<std::string> elements = split(line, ' ');

                    int x = getInt(trim(elements[2]));
                    int y = getInt(trim(elements[3]));
                    int w = getInt(trim(elements[4]));
                    int h = getInt(trim(elements[5]));

//				this->rects.push_back({x, y, w, h});
                }
            }
            file.close();
        }
    }

}