//
// Created by Michael Malura on 14/11/16.
//

#ifndef GAME_SDL_ERROR_H
#define GAME_SDL_ERROR_H

#include <string>
#include <sstream>
#include <map>

namespace Pancake {

    /**
    * Log an SDL error with some error message to the output stream of our choice
    * @param os The output stream to write the message to
    * @param msg The error message to write, format will be msg error: SDL_GetError()
    */
    void logSDLError(std::ostream& os, const std::string& msg);

    class Log;

    typedef Log* LogHandle;
    typedef std::map<const std::string, LogHandle> Logs;

    class Log {
    private:
        Log(std::string system);

        ~Log();

        Log(const LogHandle l);

    protected:
        static bool initialized;

        static Logs instances;

        long long messageCount = 0;

        std::string system;


    public:
        static LogHandle getInstance(std::string system = "PANCAKE");

        static void initialize();

        static void release();

        void writeLine(std::string message);

        void info(std::string message);

        void debug(std::string message);

        void error(std::string message);


    };

}

#endif //GAME_SDL_ERROR_H
