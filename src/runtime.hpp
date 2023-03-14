#pragma once
#include <cstddef>

namespace quadratics {

// Thread management and program setup. This class specifically parses CLI args
// and so `char** input` is expected to be valid for the duration of the program
class Runtime {
public:
  // Predetermined number of threads to use can be passed, passing non-positive
  // number will lead to automatic hardware thread number detection
  Runtime(int size, char** input, size_t threads = 0, size_t batch_size = 50);

  // Runtime currently does not actually have any runtime state, only initial
  // data, but it may in the future. For now is neither movable nor copyable.
  Runtime(Runtime&&) = delete;
  Runtime(const Runtime&) = delete;
  Runtime& operator=(Runtime&&) = delete;
  Runtime& operator=(const Runtime&) = delete;

  // Setup, launch and join execution threads
  void operator()();

  // Run program serially
  void serial();

private:
  static auto hardware_threads() -> size_t;

private:
  int size_;
  char** input_;
  size_t threads_;
  size_t batch_size_;
};

} // namespace quadratics