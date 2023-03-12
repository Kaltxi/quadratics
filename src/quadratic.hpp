#pragma once
#include <cmath>
#include <string>
#include <variant>

namespace quadratics {

struct Equation {
  int a;
  int b;
  int c;

  auto as_str() const -> std::string;
};

struct NoRoots {
  float min;
};

struct OneRoot {
  float x;
  float min;
};

struct TwoRoots {
  float x1;
  float x2;
  float min;
};

using Solution = std::variant<NoRoots, OneRoot, TwoRoots>;

Solution solve(Equation eq);

namespace impl {

struct AsStr {
  std::string operator()(const NoRoots& solution) const;
  std::string operator()(const OneRoot& solution) const;
  std::string operator()(const TwoRoots& solution) const;
};

struct Extremum {
  float operator()(const NoRoots& solution) const { return solution.min; }
  float operator()(const OneRoot& solution) const { return solution.min; }
  float operator()(const TwoRoots& solution) const { return solution.min; }
};

struct NumRoots {
  int operator()(const NoRoots&) const { return 0; }
  int operator()(const OneRoot&) const { return 1; }
  int operator()(const TwoRoots&) const { return 2; }
};

struct Roots {
  std::pair<float, float> operator()(const NoRoots&) const {
    return {NAN, NAN};
  }
  std::pair<float, float> operator()(const OneRoot& solution) const {
    return {solution.x, solution.x};
  }
  std::pair<float, float> operator()(const TwoRoots& solution) const {
    return {solution.x1, solution.x2};
  }
};

} // namespace impl

// Solution visitors
namespace solution {

inline std::string as_str(const Solution& solution) {
  return std::visit(impl::AsStr{}, solution);
}

inline float extremum(const Solution& solution) {
  return std::visit(impl::Extremum{}, solution);
}

inline int num_roots(const Solution& solution) {
  return std::visit(impl::NumRoots{}, solution);
}

inline std::pair<float, float> roots(const Solution& solution) {
  return std::visit(impl::Roots{}, solution);
}

} // namespace solution

} // namespace quadratics