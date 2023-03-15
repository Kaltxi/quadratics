#pragma once
#include <cmath>
#include <string>

namespace quadratics {

// Value type for quadratic equation solution (roots and extremum)
struct Solution {
  enum class Roots { None, One, Two };

  float x1;
  float x2;
  float min;
  Roots root_num;

  auto as_str() const -> std::string;
  auto num_roots() const -> int;

private:
  static auto to_str(float value) -> std::string;
};

// Value type for quadratic equation coefficient
struct Equation {
  int a;
  int b;
  int c;

  auto solve() const -> Solution;
  auto as_str() const -> std::string;
};

} // namespace quadratics