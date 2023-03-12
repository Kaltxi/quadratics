#include "runtime.hpp"
#include "equationqueue.hpp"
#include "parser.hpp"
#include "solver.hpp"
#include <thread>
#include <vector>

namespace quadratics {

Runtime::Runtime(int size, char** input, std::size_t threads)
    : size_(size), input_(input), threads_(threads) {}

void Runtime::operator()() {
  // Minimum number of threads used is 2 - one for parser and one for solver
  // Additional solvers are launched when more threads available
  const size_t hardware_threads =
      threads_ <= 0 ? std::thread::hardware_concurrency() : threads_;
  const size_t threads_to_use = hardware_threads > 1 ? hardware_threads - 1 : 1;

  EquationQueue queue;
  std::mutex stdout_mutex;

  std::vector<std::thread> threads;
  threads.reserve(threads_to_use + 1);

  threads.emplace_back(Parser{Data{size_, input_}, queue});

  for (size_t i = 0; i < threads_to_use; ++i) {
    threads.emplace_back(Solver{queue, stdout_mutex});
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

} // namespace quadratics