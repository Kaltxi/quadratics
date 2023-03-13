#include "parser.hpp"
#include "quadratic.hpp"
#include <stdexcept>
#include <string>

namespace quadratics {

Parser::Parser(const Data data, EquationQueue& queue)
    : data_(data), queue_(queue) {}

void Parser::operator()() {
  auto [mutex, data_ready] = queue_.subscribe();

  while (true) {
    const auto eq = next_equation();

    if (!eq) {
      const std::lock_guard lock{mutex};
      queue_.set_data_ended(true);
      data_ready.notify_all();
      break;
    }

    const std::lock_guard lock{mutex};
    queue_.push(eq.value());
    data_ready.notify_one();
  }
}

auto Parser::next_equation() -> std::optional<Equation> {
  auto left = data_.size - current_pos_;

  while (left > 0) {
    auto tail = left >= 3 ? 3 : left;

    auto a = data_.input[current_pos_];
    auto b = tail >= 2 ? data_.input[current_pos_ + 1] : 0;
    auto c = tail >= 3 ? data_.input[current_pos_ + 2] : 0;

    try {
      const Equation eq{std::stoi(a), std::stoi(b), std::stoi(c)};
      current_pos_ += tail;
      return eq;
    } catch (const std::invalid_argument&) {
      current_pos_ += tail;
      left -= tail;
      continue;
    }
  }

  return {};
}

} // namespace quadratics