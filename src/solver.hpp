#pragma once
#include "equationqueue.hpp"
#include <cstddef>
#include <mutex>

namespace quadratics {

// Consumes queue of quadratic equations by solving them and sending the results
// to `stdin`
class Solver {
public:
  Solver(EquationQueue& queue, std::mutex& stdout_mutex, size_t batch_size = 1);

  // Move constructible to be used as thread functor
  Solver(Solver&&) = default;
  Solver(const Solver&) = delete;
  Solver& operator=(Solver&&) = delete;
  Solver& operator=(const Solver&) = delete;

  // Solver execution loop
  void operator()();

  // Ignore locks for serial execution
  void serial();

private:
  // Taking the queue as a reference, as it is a necessary precondition for its
  // lifetime to be valid during parser execution
  EquationQueue& queue_;
  std::mutex& stdout_mutex_;
  size_t batch_size_;
};

} // namespace quadratics