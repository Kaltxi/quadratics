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
    if (left >= 3) {

      try {
        const Equation eq{std::stoi(data_.input[current_pos_]),
                          std::stoi(data_.input[current_pos_ + 1]),
                          std::stoi(data_.input[current_pos_ + 2])};
        current_pos_ += 3;
        return eq;
      } catch (const std::invalid_argument&) {
        current_pos_ += 3;
        left -= 3;
        continue;
      }
    }

    if (left == 2) {
      try {
        const Equation eq{std::stoi(data_.input[current_pos_]),
                          std::stoi(data_.input[current_pos_ + 1]), 0};
        current_pos_ += 2;
        return eq;
      } catch (const std::invalid_argument&) {
        current_pos_ += 2;
        left -= 2;
        continue;
      }
    }

    if (left == 1) {
      try {
        const Equation eq{std::stoi(data_.input[current_pos_]), 0, 0};
        current_pos_ += 1;
        return eq;
      } catch (const std::invalid_argument&) {
        current_pos_ += 1;
        left -= 1;
        continue;
      }
    }
  }

  return {};
}

} // namespace quadratics