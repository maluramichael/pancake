//
// Created by Michael Malura on 14/11/16.
//

#include <string>
#include <iostream>
#include <SDL_quit.h>

#include "../include/Log.h"

namespace Pancake {

    void logSDLError(std::ostream &os, const std::string &msg) {
        os << msg << " error: " << SDL_GetError() << std::endl;
    }

}