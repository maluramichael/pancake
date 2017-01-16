//
// Created by Michael Malura on 22/11/16.
//

#include <fstream>
#include <vector>
#include "../libs/json/src/json.hpp"

#include "../include/Map.h"

using json = nlohmann::json;

namespace Pancake {

    Pancake::Map::Map(std::string path) {
        std::ifstream file;
        file.open(path);

        if (file.is_open()) {

            std::string line;
            std::string content;

            while (getline(file, line)) {
                content += line + '\n';
            }

            file.close();

            json document = json::parse(content);
            json settings = document["settings"];
            json data = document["data"];

            width = settings["width"];
            height = settings["height"];
            std::cout << "Width: " << width << " Height: " << height << '\n';

            this->data = new int[width * height];

            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    *(this->data + (y * width) + x) = data.at(y).at(x).get<int>();
                }
            }
        }
    }

    Map::~Map() {
        if (data != nullptr) {
            delete data;
        }
    }

}