#include "equationqueue.hpp"

namespace quadratics {

auto EquationQueue::subscribe()
    -> std::pair<std::mutex&, std::condition_variable&> {
  return {mutex_, data_available_};
}

auto EquationQueue::pop() -> Equation {
  auto front = queue_.front();
  queue_.pop();
  return front;
}

auto EquationQueue::empty() const -> int { return queue_.empty(); }

auto EquationQueue::data_ended() const -> bool { return data_ended_; }

void EquationQueue::push(Equation eq) { queue_.push(eq); }

void EquationQueue::set_data_ended(const bool ended) { data_ended_ = ended; }

} // namespace quadratics