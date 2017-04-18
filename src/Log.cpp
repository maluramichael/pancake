//
// Created by Michael Malura on 14/11/16.
//

#include <string>
#include <iostream>
#include <SDL_quit.h>

#include "../include/Log.h"

namespace Pancake {

    void logSDLError(std::ostream& os, const std::string& msg) {
        os << msg << " error: " << SDL_GetError() << std::endl;
    }

    Logs Log::instances = Logs();

    Log::Log(std::string system) {
        this->system = system;
    }

    Log::~Log() {

    }

    Log::Log(const Log& l) : system(l.system) {

    }

    void Log::writeLine(std::string message) {
        std::cout << '[' << system << ']' << '[' << (messageCount++) << ']' << ' ' << message << '\n';
    }

    void Log::info(std::string message) {
        writeLine(message);
    }

    void Log::debug(std::string message) {
        writeLine(message);
    }

    void Log::error(std::string message) {
        writeLine(message);
    }

    Log& Log::getInstance(std::string system) {
        if (Log::instances.find(system) == Log::instances.end()) {
            Log::instances.insert(std::pair<std::string, Log*>(system, new Log(system)));
        }
        return *Log::instances[system];
    }

    void Log::initialize() {
        Log::getInstance("LOG").info("Initialize log");
    }

    void Log::release() {
        Log::getInstance("LOG").info("Release log");
        for (auto pair : Log::instances) {
            delete pair.second;
            pair.second = nullptr;
        }
    }
}