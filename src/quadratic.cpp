#include "quadratic.hpp"
#include <array>
#include <charconv>
#include <string>

namespace quadratics {

auto Solution::as_str() const -> std::string {
  // Reserve strings to common lengths, pay the price of reallocation when
  // the numbers are uncommonly large
  switch (root_num) {
  case Roots::None: {
    std::string str;
    str.reserve(25);
    str.append("no roots Xmin=");
    str.append(to_str(min));
    return str;
  }
  case Roots::One: {
    std::string str;
    str.reserve(30);
    str.append("(");
    str.append(to_str(x1));
    str.append(") Xmin=");
    str.append(to_str(min));
    return str;
  }
  case Roots::Two: {
    std::string str;
    str.reserve(45);
    str.append("(");
    str.append(to_str(x1));
    str.append(",");
    str.append(to_str(x2));
    str.append(") Xmin=");
    str.append(to_str(min));
    return str;
  }
  }
}

auto Solution::num_roots() const -> int {
  if (root_num == Roots::None) {
    return 0;
  } else if (root_num == Roots::One) {
    return 1;
  } else {
    return 2;
  }
}

auto Solution::to_str(const float value) -> std::string {
  // `to_chars` is a more performant `to_string` implementation, but requires
  // preallocation. Preallocate 15 characters, and if it is not enough
  // fall back to `to_string`
  std::array<char, 15> str;
  auto [ptr, error] = std::to_chars(str.data(), str.data() + str.size(), value);

  if (error == std::errc{}) {
    return std::string(str.data(), ptr);
  } else {
    return std::to_string(value);
  }
}

auto Equation::solve() const -> Solution {
  const auto af = static_cast<float>(a);
  const auto bf = static_cast<float>(b);
  const auto cf = static_cast<float>(c);

  // Parallel to x line
  if (a == 0 && b == 0) {
    const auto extremum_ = cf;
    return Solution{NAN, NAN, extremum_, Solution::Roots::None};
  }

  // Linear equation
  if (a == 0) {
    const auto root = -cf / bf;
    return Solution{root, root, root, Solution::Roots::One};
  }

  const auto discriminant = b * b - 4 * a * c;
  const auto extremum_ = -0.5f * bf / af;

  // No roots
  if (discriminant < 0) {
    return Solution{NAN, NAN, extremum_, Solution::Roots::None};
  }

  // One root
  if (discriminant == 0) {
    const auto root = extremum_;
    return Solution{root, root, extremum_, Solution::Roots::One};
  }

  // Two roots
  const auto half_width =
      0.5f * std::sqrt(static_cast<float>(discriminant)) / af;
  const auto root1 = extremum_ - half_width;
  const auto root2 = extremum_ + half_width;

  return Solution{root1, root2, extremum_, Solution::Roots::Two};
}

auto Equation::as_str() const -> std::string {
  std::string str;
  str.reserve(15);
  str.append("(");
  str.append(std::to_string(a));
  str.append(" ");
  str.append(std::to_string(b));
  str.append(" ");
  str.append(std::to_string(c));
  str.append(")");
  return str;
}

} // namespace quadratics