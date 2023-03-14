#pragma once
#include "quadratic.hpp"
#include "rdtsc.hpp"
#include "runtime.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace quadratics {

inline void print_vec(const std::vector<std::string>& vec) {
  for (auto& string : vec) {
    std::cout << string;
  }
}

inline std::string format_clocks(std::pair<double, uint64_t> data) {
  return std::to_string(data.first) + " " + std::to_string(data.second) + "\n";
}

// Measure a single equation solution
inline std::string bench_solve() {
  Equation no_roots_eq{2, 2, 2};
  auto no_roots_fn = [no_roots_eq] { solve(no_roots_eq); };
  auto no_roots = clocks_with_median(no_roots_fn);

  Equation one_root_eq{2, 2, 2};
  auto one_root_fn = [one_root_eq] { solve(one_root_eq); };
  auto one_root = clocks_with_median(one_root_fn);

  Equation two_roots_eq{1, -2, 1};
  auto two_roots_fn = [two_roots_eq] { solve(two_roots_eq); };
  auto two_roots = clocks_with_median(two_roots_fn);

  // clang-format off
  return "SOLVE QUADRATIC EQUATION\n"
         "  No roots: " + format_clocks(no_roots) +
         "  One root: " + format_clocks(one_root) +
         "  Two roots: " + format_clocks(two_roots);
  // clang-format on
}

// Measure whole runtime, both threaded and serial
inline std::string bench_runtime(int size, char** input) {
  Runtime runtime{size, input, 0};
  auto threaded = clocks_with_median(runtime);
  auto serial = clocks_with_median([&runtime] { runtime.serial(); });

  return "FULL RUNTIME WITH PASSED ARGS:\n"
         "  Threaded runtime: " +
         format_clocks(threaded) + "  Serial runtime: " + format_clocks(serial);
}

} // namespace quadratics