//
// Created by Michael Malura on 22/11/16.
//

#ifndef GAME_MAP_H
#define GAME_MAP_H

#include <string>

namespace Pancake {

    class Map {
    public:
        int *data = nullptr;
        int width = 0;
        int height = 0;

        Map(std::string path);

        ~Map();
    };

}

#endif //GAME_MAP_H
