//
// Created by Michael Malura on 14/11/16.
//

#ifndef GAME_SDL_ERROR_H
#define GAME_SDL_ERROR_H

namespace Pancake {

    /**
    * Log an SDL error with some error message to the output stream of our choice
    * @param os The output stream to write the message to
    * @param msg The error message to write, format will be msg error: SDL_GetError()
    */
    void logSDLError(std::ostream &os, const std::string &msg);
}

#endif //GAME_SDL_ERROR_H
