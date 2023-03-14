#pragma once
#include "equationqueue.hpp"
#include "quadratic.hpp"
#include <array>
#include <cstddef>
#include <optional>

namespace quadratics {

struct Data {
  int size;
  char** input;
};

// Parses input list of strings into quadratic equation coefficients stroring
// them in the queue
class Parser {
public:
  Parser(Data data, EquationQueue& queue, size_t batch_size = 0);

  // Move constructible to be used as thread functor
  Parser(Parser&&) = default;
  Parser(const Parser&) = delete;
  Parser& operator=(Parser&&) = delete;
  Parser& operator=(const Parser&) = delete;
  ~Parser() = default;

  // Parser execution loop
  void operator()();

private:
  static auto parse_coefficients(int position, int tail, char** inputs)
      -> std::optional<std::array<int, 3>>;

  // Retrieve next equation or nothing if data end reached
  auto next_equation() -> std::optional<Equation>;

private:
  Data data_;
  int current_pos_{0};
  size_t batch_size_;
  EquationQueue& queue_;
};

} // namespace quadratics