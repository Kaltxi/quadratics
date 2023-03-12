#include "quadratic.hpp"
#include <iostream>

using namespace quadratics;

int main() {
  Equation eq{1, -6, 9};
  Solution sol(solve(eq));
  std::cout << solution::as_str(sol) << std::endl;
}