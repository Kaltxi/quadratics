#pragma once
#include "quadratic.hpp"
#include <condition_variable>
#include <mutex>
#include <queue>

namespace quadratics {

// Queue wrapper for producer-consumer communication with quadratic equations'
// coefficients
class EquationQueue {
public:
  EquationQueue() = default;

  // This is thread-driven queue, no reason to neither move nor copy
  EquationQueue(EquationQueue&&) = delete;
  EquationQueue(const EquationQueue&) = delete;
  EquationQueue& operator=(EquationQueue&&) = delete;
  EquationQueue& operator=(const EquationQueue&) = delete;

  // Queue is not thread safe - sync with provided `mutex` and notify of
  // available data via provided `condition_variable`
  auto subscribe() -> std::pair<std::mutex&, std::condition_variable&>;

  // Consumer interface
  auto pop() -> Equation;
  auto empty() const -> int;
  auto data_ended() const -> bool;

  // Producer interface
  void push(Equation eq);
  void set_data_ended(bool ended);

private:
  std::queue<Equation> queue_{};
  std::mutex mutex_{};
  std::condition_variable data_available_{};
  bool data_ended_{false};
};

} // namespace quadratics