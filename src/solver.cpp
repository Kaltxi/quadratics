#include "solver.hpp"
#include "equationqueue.hpp"
#include "quadratic.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace quadratics {

Solver::Solver(EquationQueue& queue, std::mutex& stdout_mutex,
               const size_t batch_size)
    : queue_(queue), stdout_mutex_(stdout_mutex), batch_size_(batch_size) {}

void Solver::operator()() {
  auto [mutex, data_ready] = queue_.subscribe();

  std::vector<Equation> equations;
  equations.reserve(batch_size_);

  std::vector<std::string> solutions;

  while (true) {
    equations.clear();
    solutions.clear();

    std::unique_lock queue_lock(mutex);
    data_ready.wait(queue_lock,
                    [this] { return !queue_.empty() || queue_.data_ended(); });

    if (queue_.empty() && queue_.data_ended()) {
      break;
    }

    for (size_t i = 0; i < batch_size_ && !queue_.empty(); ++i) {
      equations.push_back(queue_.pop());
    }
    queue_lock.unlock();

    for (const auto eq : equations) {
      const auto sol = eq.solve();
      solutions.push_back(eq.as_str() + " => " + sol.as_str() + "\n");
    }

    const std::lock_guard stdout_lock(stdout_mutex_);
    for (const auto& solution : solutions) {
      std::cout << solution;
    }
  }
}

void Solver::serial() {
  std::vector<Equation> equations;
  equations.reserve(batch_size_);

  std::vector<std::string> solutions;

  while (true) {
    equations.clear();
    solutions.clear();

    if (queue_.empty() && queue_.data_ended()) {
      break;
    }

    for (size_t i = 0; i < batch_size_ && !queue_.empty(); ++i) {
      equations.push_back(queue_.pop());
    }

    for (const auto eq : equations) {
      const auto sol = eq.solve();
      std::string result;
      result.reserve(60);
      result.append(eq.as_str());
      result.append(" => ");
      result.append(sol.as_str());
      result.append("\n");
      solutions.push_back(result);
    }
    for (const auto& solution : solutions) {
      std::cout << solution;
    }
  }
}

} // namespace quadratics