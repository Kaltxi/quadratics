#include "quadratic.hpp"
#include <doctest/doctest.h>
#include <utility>

using namespace quadratics;

// Warning: floating-point operations and equivalence depend on the order of
// operations

TEST_CASE("Quadratic equation with two roots is solved correctly") {
  const Equation eq{1, -2, -3};

  const auto sol = solve(eq);
  const auto roots = solution::roots(sol);

  CHECK(roots.first == -1.f);
  CHECK(roots.second == 3.f);
  CHECK(solution::extremum(sol) == 1.f);
}

// Even though technically the correct extremum is Inf or -Inf, as per
// specification it should be equal to the root
TEST_CASE("Liniearly degenerate equation has one root and extremum made equal "
          "to it") {
  const Equation eq{0, 4, -4};

  const auto sol = solve(eq);
  const auto roots = solution::roots(sol);

  CHECK(roots.first == 1.f);
  CHECK(roots.second == 1.f);
  CHECK(solution::extremum(sol) == 1.f);
}

TEST_CASE("Always positive quadratic equation has no roots") {
  const Equation eq{11, 2, 2};

  const auto sol = solve(eq);

  const auto right_extremum = -0.5f * 2.f / 11.f;

  CHECK(solution::num_roots(sol) == 0);
  CHECK(solution::extremum(sol) == right_extremum);
}

// Equations like `c = 0`
TEST_CASE("Constant equation has no roots and extremum eqaul to the constant") {
  const Equation eq{0, 0, -2};

  const auto sol = solve(eq);

  CHECK(solution::num_roots(sol) == 0);
  CHECK(solution::extremum(sol) == -2.f);
}

// There exists one exception to the rule: the case of `0 = 0` when there are
// actually infinite number of solutions, we ignore it for interface homogeneity
TEST_CASE("Constant equation with c = 0 leads to no roots, despire inifite "
          "number of them") {
  const Equation eq{0, 0, 0};

  const auto sol = solve(eq);

  CHECK(solution::num_roots(sol) == 0);
  CHECK(solution::extremum(sol) == 0.f);
}