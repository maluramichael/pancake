//
// Created by Michael Malura on 17/11/16.
//

#include <iostream>
#include <fstream>
#include <SDL_rect.h>
#include <map>
#include <vector>
#include "../libs/json/src/json.hpp"
#include "../include/TextureAtlas.h"

using json = nlohmann::json;
using namespace Pancake;

TextureAtlas::TextureAtlas(std::string path) {
    this->rects.push_back(SDL_Rect());

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
        json tiles = document["tiles"];

        for (json::iterator tile = tiles.begin(); tile != tiles.end(); ++tile) {

            std::string dump = (*tile).dump();

            int x = 0;
            int y = 0;
            int w = 0;
            int h = 0;
            std::string key;

            for (json::iterator object = (*tile).begin(); object != (*tile).end(); ++object) {
                key = object.key();
                if (key == "x") {
                    x = atoi((*object).get<std::string>().c_str());
                } else if (key == "y") {
                    y = atoi((*object).get<std::string>().c_str());
                } else if (key == "width") {
                    w = atoi((*object).get<std::string>().c_str());
                } else if (key == "height") {
                    h = atoi((*object).get<std::string>().c_str());
                }
            }

            this->rects.push_back({x, y, w, h});
        }
    }
}

SDL_Rect &TextureAtlas::addSprite(int x, int y, int w, int h) {
    this->rects.push_back(SDL_Rect());
    return *this->rects.end();
}

SDL_Rect &TextureAtlas::getSprite(int index) {
    return this->rects[0];
}

SDL_Rect &TextureAtlas::operator[](int x) {
    return this->rects[x];
}
