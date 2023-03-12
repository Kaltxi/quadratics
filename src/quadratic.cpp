#include "quadratic.hpp"
#include <cmath>

namespace quadratics {

Solution solve(Equation eq) {
  const auto a = static_cast<float>(eq.a);
  const auto b = static_cast<float>(eq.b);
  const auto c = static_cast<float>(eq.c);

  if (eq.a == 0 && eq.b == 0) {
    const auto extremum_ = c;
    return NoRoots{extremum_};
  }

  if (eq.a == 0) {
    const auto root = -c / b;
    return OneRoot{root, root};
  }

  const auto discriminant = eq.b * eq.b - 4 * eq.a * eq.c;
  const auto extremum_ = -0.5f * b / a;

  if (discriminant < 0) {
    return NoRoots{extremum_};
  }

  if (discriminant == 0) {
    const auto root = extremum_;
    return OneRoot{root, root};
  }

  const auto half_width =
      0.5f * std::sqrt(static_cast<float>(discriminant)) / a;
  const auto root1 = extremum_ - half_width;
  const auto root2 = extremum_ + half_width;

  return TwoRoots{root1, root2, extremum_};
}

std::string impl::AsStr::operator()(const NoRoots& solution) const {
  return {"no roots Xmin=" + std::to_string(solution.min)};
}

std::string impl::AsStr::operator()(const OneRoot& solution) const {
  return {"(" + std::to_string(solution.x) +
          ") Xmin=" + std::to_string(solution.min)};
}

std::string impl::AsStr::operator()(const TwoRoots& solution) const {
  return {"(" + std::to_string(solution.x1) + ',' +
          std::to_string(solution.x2) +
          ") Xmin=" + std::to_string(solution.min)};
}

} // namespace quadratics