#pragma once
#include <cmath>
#include <string>
#include <variant>

namespace quadratics {

struct Solution {
  enum class Roots { None, One, Two };

  float x1;
  float x2;
  float min;
  Roots root_num;

  auto as_str() const -> std::string;
  auto num_roots() const -> int;
};

struct Equation {
  int a;
  int b;
  int c;

  auto solve() const -> Solution;
  auto as_str() const -> std::string;
};

} // namespace quadratics