#include "solver.hpp"
#include "equationqueue.hpp"
#include "quadratic.hpp"
#include <iostream>

namespace quadratics {

Solver::Solver(EquationQueue& queue, std::mutex& stdout_mutex)
    : queue_(queue), stdout_mutex_(stdout_mutex) {}

void Solver::operator()() {
  auto [mutex, data_ready] = queue_.subscribe();

  while (true) {
    std::unique_lock queue_lock(mutex);
    data_ready.wait(queue_lock,
                    [this] { return !queue_.empty() || queue_.data_ended(); });

    if (queue_.empty() && queue_.data_ended()) {
      break;
    }

    const auto eq = queue_.pop();
    queue_lock.unlock();

    const auto sol = solve(eq);

    const std::lock_guard stdout_lock(stdout_mutex_);
    std::cout << eq.as_str() << " => " << solution::as_str(sol) << "\n";
  }
}

} // namespace quadratics