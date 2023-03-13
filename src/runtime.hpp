#pragma once
#include <cstddef>

namespace quadratics {

// Thread management and program setup
class Runtime {
public:
  // Predetermined number of threads to use can be passed, passing non-positive
  // number will lead to automatic hardware thread number detection
  Runtime(int size, char** input, std::size_t threads = 0);

  // Setup, launch and join execution threads
  void operator()();

  // Run program serially
  void serial();

private:
  int size_;
  char** input_;
  std::size_t threads_;
};

} // namespace quadratics