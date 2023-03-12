#pragma once
#include "equationqueue.hpp"
#include "quadratic.hpp"
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
  Parser(Data data, EquationQueue& queue);

  // Move constructible to be used as thread functor
  Parser(Parser&&) = default;
  Parser(const Parser&) = delete;
  Parser& operator=(Parser&&) = delete;
  Parser& operator=(const Parser&) = delete;
  ~Parser() = default;

  // Parser execution loop
  void operator()();

private:
  // Retrieve next equation or nothing if data end reached
  auto next_equation() -> std::optional<Equation>;

private:
  Data data_;
  int current_pos_{1}; // currently going over raw argv[], skipping program name
  EquationQueue& queue_;
};

} // namespace quadratics