#ifndef PANCAKE_PROFILERSAMPLE
#define PANCAKE_PROFILERSAMPLE

#include <iostream>

class ProfilerSample {
public:
  const char* name;
  
  ProfilerSample(const char* name) : name(name) {
  }
  
  ~ProfilerSample() {
    std::cout << "[PROFILER] " << name << " took 9ms\n";
  }
};

#define PROFILE(name) ProfilerSample ___sample(name)

#endif
