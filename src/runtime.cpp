#include "runtime.hpp"
#include "equationqueue.hpp"
#include "parser.hpp"
#include "solver.hpp"
#include <algorithm>
#include <thread>
#include <vector>

namespace quadratics {

Runtime::Runtime(const int size, char** input, const size_t threads,
                 const size_t batch_size)
    : size_(size), input_(input), threads_(threads), batch_size_(batch_size) {}

void Runtime::operator()() {
  // Minimum number of threads used is 2 - one for parser and one for solver
  // Additional solvers are launched when more threads are available
  const size_t recommended_threads =
      threads_ <= 0 ? hardware_threads() : threads_;

  // Don't spin extra threads when there aren't enough batches to saturate them
  const size_t max_threads =
      (static_cast<size_t>(size_) + batch_size_ - 1) / batch_size_;
  const size_t solver_threads = std::min(recommended_threads, max_threads);

  EquationQueue queue;
  std::mutex stdout_mutex;

  std::vector<std::thread> threads;
  threads.reserve(solver_threads + 1);

  threads.emplace_back(Parser{Data{size_, input_}, queue, batch_size_});

  for (size_t i = 0; i < solver_threads; ++i) {
    threads.emplace_back(Solver{queue, stdout_mutex, batch_size_});
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

void Runtime::serial() {
  EquationQueue queue;
  std::mutex stdout_mutex;
  Parser parser{Data{size_, input_}, queue, batch_size_};
  Solver solver{queue, stdout_mutex, batch_size_};

  parser();
  solver();
}

auto Runtime::hardware_threads() -> size_t {
  const size_t reported = std::thread::hardware_concurrency();
  const size_t actual = reported > 0 ? reported : 1;
  return actual;
}

} // namespace quadratics