#ifndef PANCAKE_PROFILERSAMPLE
#define PANCAKE_PROFILERSAMPLE

#include <iostream>

class ProfilerSample {
public:
  const char* name;
  
  ProfilerSample(const char* name) : name(name) {
    std::cout << "[PROFILER_START] " << name << "\n";
  }
  
  ~ProfilerSample() {
    std::cout << "[  PROFILER_END] " << name << "\n";
  }
};

#define PROFILE(name) ProfilerSample ___sample(name)

#endif
