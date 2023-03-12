#pragma once
#include "equationqueue.hpp"
#include <mutex>

namespace quadratics {

// Consumes queue of quadratic equations by solving them and sending the results
// to `stdin`
class Solver {
public:
  Solver(EquationQueue& queue, std::mutex& stdout_mutex);

  // Move constructible to be used as thread functor
  Solver(Solver&&) = default;
  Solver(const Solver&) = delete;
  Solver& operator=(Solver&&) = delete;
  Solver& operator=(const Solver&) = delete;

  // Solver execution loop
  void operator()();

private:
  EquationQueue& queue_;
  std::mutex& stdout_mutex_;
};

} // namespace quadratics