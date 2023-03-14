#include "parser.hpp"
#include "quadratic.hpp"
#include <array>
#include <charconv>
#include <cstring>
#include <vector>

namespace quadratics {

Parser::Parser(const Data data, EquationQueue& queue, const size_t batch_size)
    : data_(data), batch_size_(batch_size), queue_(queue) {}

void Parser::operator()() {
  auto [mutex, data_ready] = queue_.subscribe();

  std::vector<Equation> equations;
  equations.reserve(batch_size_);

  while (true) {
    equations.clear();

    // Parse a batch of equations
    for (size_t i = 0; i < batch_size_; ++i) {
      const auto eq = next_equation();

      if (!eq) {
        break;
      }

      equations.push_back(eq.value());
    }

    if (equations.empty()) {
      const std::lock_guard lock{mutex};
      queue_.set_data_ended(true);
      data_ready.notify_all();
      break;
    }

    const std::lock_guard lock{mutex};
    for (const auto eq : equations) {
      queue_.push(eq);
    }
    data_ready.notify_one();
  }
}

auto Parser::parse_coefficients(int position, int tail, char** input)
    -> std::optional<std::array<int, 3>> {
  std::array<int, 3> coefs{};

  for (int i = 0; i < 3; ++i) {
    // Only attempt to parse of there are string left
    if (tail >= i + 1) {
      const auto* str = input[position + i];
      const auto len = std::strlen(str);
      const auto result =
          std::from_chars(str, str + len, coefs[static_cast<size_t>(i)]);

      if (result.ec == std::errc::invalid_argument ||
          result.ec == std::errc::result_out_of_range) {
        return {};
      }
    }
  }

  return coefs;
}

auto Parser::next_equation() -> std::optional<Equation> {
  auto left = data_.size - current_pos_;

  // Advance trey by trey until no more input strings left
  while (left > 0) {
    const auto tail = left >= 3 ? 3 : left;

    const auto parse = parse_coefficients(current_pos_, tail, data_.input);

    current_pos_ += tail;

    if (parse) {
      const auto coefs = parse.value();
      return Equation{coefs[0], coefs[1], coefs[2]};
    }

    left -= tail;
  }

  return {};
}

} // namespace quadratics
