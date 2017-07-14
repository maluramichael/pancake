#ifndef PANCAKE_PROFILERSAMPLE
#define PANCAKE_PROFILERSAMPLE

#include <time.h>
#include <iostream>

class ProfilerSample {
public:
  const char* name;
  
  const std::clock_t start;
  
  ProfilerSample(const char* name) : name(name), start(clock()) {
    //std::cout << "[PFLR] " << name << "\n";
  }
  
  ~ProfilerSample() {
    auto time = (double(clock() - start) / CLOCKS_PER_SEC);
    
    std::cout << "[PFLR] " <<  name << " | " << time << "\n";
  }
};

#define PROFILE(name) ProfilerSample ___sample(name)

#endif
