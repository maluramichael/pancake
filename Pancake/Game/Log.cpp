#include <string>
#include <iostream>
#include <SDL_quit.h>

#include "Log.h"

void logSDLError(std::ostream& os, const std::string& msg) {
  os << msg << " error: " << SDL_GetError() << std::endl;
}

Logs Log::instances = Logs();
bool Log::initialized = false;

Log::Log(std::string system) {
  this->system = system;
}

Log::~Log() {
}

Log::Log(const LogHandle l) : system(l->system) {
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

LogHandle Log::getInstance(std::string system) {
  if (Log::instances.find(system) == Log::instances.end()) {
    Log::instances.insert(std::pair<std::string, Log*>(system, new Log(system)));
  }
  return Log::instances[system];
}

void Log::initialize() {
  Log::getInstance("LOG")->info("Initialize log");
  Log::initialized = true;
}

void Log::release() {
  Log::getInstance("LOG")->info("Release log");
  Log::initialized = false;
  for (auto pair : Log::instances) {
    delete pair.second;
    pair.second = nullptr;
  }
}